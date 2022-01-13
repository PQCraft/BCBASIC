#ifndef BCB_CMDS_H
#define BCB_CMDS_H

#include <inttypes.h>

#include "common.h"

enum {
    BCB_CMD_NULL,   // Empty line
    BCB_CMD_EXIT,   // EXIT [CODE%]
    BCB_CMD_PUT,    // PUT [DATA%|DATA$]...
    BCB_CMD_CLS,    // CLS [COLOR%] [, LINE%]
};

uint16_t runCmd(int, int, bcb_data*);   // Run a command

#endif
