if [ -z "$*" ]; then
    FILE=".changelog"
    if [ ! -f '.changelog' ]; then echo "Not a file: .changelog"; exit 1; fi
else
    for FILE in "$@"; do
        if [ ! -f "$FILE" ]; then echo "Not a file: $FILE"; exit 1; fi
    done
    FILE=""
fi
echo "**Changes:**
$(sed 's/^/- /' "$@" "$FILE")
<br>

**Binaries:**
- Linux x86 64-bit: \`BCBASIC-Linux-x86_64.zip\`
- Windows x86 64-bit: \`BCBASIC-Windows-x86_64.zip\`"
