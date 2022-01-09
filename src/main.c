#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "bcbasic.h"
#include "common.h"
#include "main.h"
#include "commands.h"

char* bcb_version = BCB_VERSION;
char* bcb_build = BCB_BUILD;
uint64_t bcb_build_id = BCB_BUILD_ID;

char* bcb_error_info = NULL;

void bcb_printError(uint16_t id) {
    if (id == BCB_ERR_NONE) return;
    fprintf(stderr, "Error %u: ", id);
    switch (id) {
        case BCB_ERR_SYNTAX:;
            fputs("Syntax", stderr);
            break;
        case BCB_ERR_TYPE_MM:;
            fputs("Type mismatch", stderr);
            break;
        case BCB_ERR_DIM_MM:;
            fputs("Dimension mismatch", stderr);
            break;
        case BCB_ERR_ARG_CT_MM:;
            fputs("Argument count mismatch", stderr);
            break;
        case BCB_ERR_UNDEF_OP:;
            fputs("Undefined operation", stderr);
            break;
        case BCB_ERR_INVAL_DATA:;
            fputs("Invalid data", stderr);
            break;
        case BCB_ERR_NO_FILE:;
            fprintf(stderr, "No such file: \"%s\"", bcb_error_info);
            break;
        case BCB_ERR_NO_DIR:;
            fprintf(stderr, "No such directory: \"%s\"", bcb_error_info);
            break;
        case BCB_ERR_NO_FD:;
            fprintf(stderr, "No such file or directory: \"%s\"", bcb_error_info);
            break;
        case BCB_ERR_NOT_FILE:;
            fprintf(stderr, "Not a file: \"%s\"", bcb_error_info);
            break;
        case BCB_ERR_NOT_DIR:;
            fprintf(stderr, "Not a directory: \"%s\"", bcb_error_info);
            break;
        case BCB_ERR_INVAL_CMD:;
            fputs("Invalid command", stderr);
            break;
        case BCB_ERR_INVAL_FUNC:;
            fputs("Invalid function", stderr);
            break;
        case BCB_ERR_INVAL_VAR:;
            fputs("Invalid variable or array name", stderr);
            break;
        case BCB_ERR_INVAL_LABEL:;
            fputs("Invalid label name", stderr);
            break;
        case BCB_ERR_MEMORY:;
            fputs("Memory", stderr);
            break;
    }
    putc('\n', stderr);
}

bool bcb_castNum(bcb_data data, int type, void* result) {
    if (data.type == BCB_TYPE_NONE || data.type == BCB_TYPE_STRING) return false;
    /*
    if (data.type >= BCB_TYPE_INT && data.type <= BCB_TYPE_UINT) {
        *((unsigned*)result) 
    }
    */
    return true;
}

int main(int argc, char** argv) {
    printf("ByteCodeBASIC version %s %s (build %lld)\n", bcb_version, bcb_build, (long long)bcb_build_id);
    return 0;
}
