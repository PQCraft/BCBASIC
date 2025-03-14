#!/bin/bash

{

I="\e[0m\e[1m\e[37m[\e[36mI\e[37m]\e[0m"
E="\e[0m\e[1m\e[37m[\e[31mX\e[37m]\e[0m"
Q="\e[0m\e[1m\e[37m[\e[32m?\e[37m]\e[0m"
T="\e[0m\e[1m\e[33m>>>\e[0m"
TB="\e[0m\e[1m\e[37m"
TR="\e[0m"
inf() { printf "${I} ${TB}${1}${TR}\n"; }
err() { printf "${E} ${TB}${1}${TR}\n"; }
qry() { printf "${Q} ${TB}${1}${TR}\n"; }
tsk() { printf "${T} ${TB}${1}${TR}\n"; }

ask() {
    RESPONSE=""
    printf "${Q} ${1}" >&2
    read RESPONSE
}
pause() {
    ask "${TB}Press enter to continue...${TR}"
}
_exit() {
    local ERR="$?"
    [[ $# -eq 0 ]] || local ERR="$1"
    err "Error ${ERR}"
    exit "${ERR}"
}

_tar() { rm -f "${1}"; tar --transform 's/.*\///g' -zc -f "${1}" ${@:2} 1> /dev/null; }
_zip() { rm -f "${1}"; zip -j -r -9 "${1}" ${@:2} 1> /dev/null; }
_tar_r() { rm -f "${1}"; tar -zc -f "${1}" ${@:2} 1> /dev/null; }
_zip_r() { rm -f "${1}"; zip -r -9 "${1}" ${@:2} 1> /dev/null; }

if ! (return 0 2> /dev/null); then

tsk "Getting info..."
VER_MAJOR="$(grep '#define BCB_VER_MAJOR ' src/bcbasic.h | sed 's/#define .* //')"
VER_MINOR="$(grep '#define BCB_VER_MINOR ' src/bcbasic.h | sed 's/#define .* //')"
VER_PATCH="$(grep '#define BCB_VER_PATCH ' src/bcbasic.h | sed 's/#define .* //')"
VER="${VER_MAJOR}.${VER_MINOR}.${VER_PATCH}"
printf "${I} ${TB}Version:${TR} [%s]\n" "${VER}"
getreltext() {
    sed -n '/^### DONE:$/,$p' TODO.md | tail -n +2
}
RELTEXT="$(getreltext)"
printf "${I} ${TB}Release text:${TR}\n%s\n${TB}EOF${TR}\n" "${RELTEXT}"
pause

tsk "Building..."
./build.sh || _exit
pause

tsk "Pushing..."
git add . || _exit
git commit -S -m "${VER}" -m "${RELTEXT}" || _exit
git push || _exit

tsk "Making release..."
git tag -s "${VER}" -m "${RELTEXT}" || _exit
git push --tags || _exit
gh release create "${VER}" --title "${VER}" --notes "${RELTEXT}" bcbasic*.tar.gz bcbasic*.zip || _exit
git push || _exit

tsk "Updating AUR..."
updatepkg() {
    inf "Updating ${1}..."
    local OLDCD="$(pwd)"
    cd ".aur/${1}" || _exit
    sed -e "s/^pkgver=.*/pkgver=${VER}/" PKGBUILD > .PKGBUILD
    cat .PKGBUILD > PKGBUILD
    rm .PKGBUILD
    makepkg --printsrcinfo > .SRCINFO || _exit
    git add PKGBUILD .SRCINFO || _exit
    git commit -m "${VER}" || _exit
    git push || _exit
    cd "$OLDCD"
}
updatepkg bcbasic
updatepkg bcbasic-bin

tsk "Cleaning up..."
rm -rf bcbasic*.tar.gz bcbasic*.zip

tsk "Done"
exit

fi

}
