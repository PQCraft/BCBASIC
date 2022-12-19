#!/bin/bash

{

source mkrelease.sh

NJOBS="$(nproc)"
rm -rf cavecube*.tar.gz cavecube*.zip
buildrel() {
    local TYPE="${1}"
    local PLATFORM="${2}"
    inf "Building ${TYPE} for ${PLATFORM}..."
    make ${@:3} clean 1> /dev/null || _exit
    RESPONSE=""
    while ! make ${@:3} "-j${NJOBS}" 1> /dev/null; do
        while [[ -z "${RESPONSE}" ]]; do
            ask "${TB}Build failed. Retry?${TR} (${TB}Y${TR}es/${TB}N${TR}o/${TB}C${TR}lean): "
            case "${RESPONSE,,}" in
                y | yes)
                    break
                    ;;
                n | no)
                    break
                    ;;
                c | clean)
                    make ${@:3} clean 1> /dev/null || _exit
                    ;;
                *)
                    RESPONSE=""
                    ;;
            esac
        done
        case "${RESPONSE,,}" in
            n | no)
                RESPONSE="n"
                break
                ;;
            *)
                RESPONSE=""
                ;;
        esac
    done
    [[ "${RESPONSE}" == "n" ]] || pkgrel || _exit
    make ${@:3} clean 1> /dev/null || _exit
    [[ ! "${RESPONSE}" == "n" ]] || _exit 1
}

###################
##  INTERPRETER  ##
###################

# Linux x86_64
pkgrel() { _tar "bcbasic_linux_x86_64.tar.gz" cavecube; }
buildrel "interpreter" "Linux x86_64"

## Linux i686
#pkgrel() { _tar "bcbasic_linux_i686.tar.gz" cavecube; }
#buildrel "interpreter" "Linux i686" M32=y

# Windows x86_64
pkgrel() { _zip "bcbasic_windows_x86_64.zip" cavecube.exe; }
buildrel "interpreter" "Windows x86_64" WINCROSS=y

## Windows i686
#pkgrel() { _zip "bcbasic_windows_i686.zip" cavecube.exe; }
#buildrel "interpreter" "Windows i686" WINCROSS=y M32=y

}
