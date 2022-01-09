[[ -z "${JOBS}" ]] && JOBS=8

ver="$(grep '#define BCB_VERSION ' src/bcbasic.h | sed 's/#define .* //;s/"//g')"
build="$(grep '#define BCB_BUILD ' src/bcbasic.h | sed 's/#define .* //;s/"//g')"
build_id="$(grep '#define BCB_BUILD_ID ' src/bcbasic.h | sed 's/#define .* //')"
verstr="$build $ver"

echo "Version:        [$ver]"
echo "Build:          [$build]"
echo "Version string: [$verstr]"

mkrel() {
    echo "Making $2..."
    rm -f "$2"
    $1 $4 1> /dev/null || exit $?
    zip -r "$2" $3 1> /dev/null || exit $?
    $1 $5 1> /dev/null
}

make clean
wine make clean

mkrel "make" "BCBASIC-Linux-x86_64.zip" "config/ resources/ bcbasic" "CFLAGS=-mtune=generic -j$JOBS build" "clean"
mkrel "wine make" "BCBASIC-Windows-x86_64.zip" "config/ resources/ bcbasic.exe" "CFLAGS=-mtune=generic -j$JOBS build" "clean"

git add */ Makefile README.md LICENSE *.sh
git commit -S -m "$verstr" || exit $?
git push || exit $?
git tag -s "$build_id" -m "$verstr" || exit $?
gh release create "$build_id" --title "$verstr" --notes "$(./release-text.sh)" *.zip || exit $?
