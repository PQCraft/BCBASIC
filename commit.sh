[[ -z "${JOBS}" ]] && JOBS=$(nproc)

ver="$(grep '#define BCB_VERSION ' src/bcbasic.h | sed 's/#define .* //;s/"//g')"
build="$(grep '#define BCB_BUILD ' src/bcbasic.h | sed 's/#define .* //;s/"//g')"
build_id="$(grep '#define BCB_BUILD_ID ' src/bcbasic.h | sed 's/#define .* //')"
verstr="$build $ver"
chlog="$(cat .changelog)"

echo "Version:        [$ver]"
echo "Build:          [$build]"
echo "Build ID:       [$build_id]"
echo "Version string: [$verstr]"
echo "Changelog:      ["$'\n'"$chlog"$'\n'"]"

mkrel() {
    echo "Making $2..."
    rm -f "$2"
    $1 $4 1> /dev/null || exit $?
    zip -r "$2" $3 1> /dev/null || exit $?
    $1 $5 1> /dev/null
}

reltext() {
    [ -z "$chlog" ] || echo "**Changes:**"$'\n'\
    "$(echo "$@" | sed 's/^/- /')"$'\n'\
    "<br>"$'\n'\
    $'\n'
    echo "**Binaries:**"$'\n'\
    "- Linux x86 64-bit: \`BCBASIC-Linux-x86_64.zip\`"$'\n'\
    "- Windows x86 64-bit: \`BCBASIC-Windows-x86_64.zip\`"
}

make clean
make BINEXT=.exe clean

mkrel "make" "BCBASIC-Linux-x86_64.zip" "bcbasic" "CFLAGS=-mtune=generic -j$JOBS build" "clean"
mkrel "make" "BCBASIC-Windows-x86_64.zip" "bcbasic.exe" "BINEXT=.exe CC=x86_64-w64-mingw32-gcc ELIB=lib/win64 CFLAGS=-mtune=generic -j$JOBS build" "clean"

git add src/ Makefile README.md LICENSE *.sh
git commit -S -m "$verstr" -m "$chlog" || exit $?
git push || exit $?
git tag -s "$ver" -m "$verstr" || exit $?
git pull --tags -f || exit $?
git push --tags || exit $?
gh release create "$ver" --title "$verstr" --notes "$(reltext "$chlog")" *.zip || exit $?

cd .aur
./update.sh "$ver"
cd ..
