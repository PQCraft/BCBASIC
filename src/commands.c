#include <stdlib.h>

#include "commands.h"
#include "common.h"

uint16_t runCmd(int id, int argc, bcb_data* args) {
    switch (id) {
        case BCB_CMD_EXIT:;
            if (argc > 0) {return BCB_ERR_ARG_CT_MM;}
            exit(0);
            return BCB_ERR_NONE;
            break;
        case BCB_CMD_PUT:;
            break;
    }
    return BCB_ERR_INVAL_CMD;
}
