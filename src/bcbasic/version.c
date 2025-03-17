#include "version.h"

void BCB_GetVersion(unsigned ver[3]) {
    ver[0] = BCB_VER_MAJOR;
    ver[1] = BCB_VER_MINOR;
    ver[2] = BCB_VER_PATCH;
}
