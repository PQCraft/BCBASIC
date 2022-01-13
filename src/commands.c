#include <stdlib.h>

#include "common.h"
#include "commands.h"
#include "main.h"

uint16_t runCmd(int id, int argc, bcb_data* args) {
    switch (id) {
        case BCB_CMD_NULL:;
            return BCB_ERR_NONE;
            break;
        case BCB_CMD_EXIT:;
            if (argc > 1) {return BCB_ERR_ARG_CT_MM;}
            uint64_t ecode = 0;
            if (argc) {
                //solveArg(&args[0]);
                if (!getUintData(&args[0], &ecode)) return BCB_ERR_TYPE_MM;
            }
            exit((uint8_t)ecode);
            return BCB_ERR_NONE;
            break;
        case BCB_CMD_PUT:;
            return BCB_ERR_NONE;
            break;
    }
    return BCB_ERR_INVAL_CMD;
}
