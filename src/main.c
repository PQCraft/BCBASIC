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
unsigned long bcb_build_id = BCB_BUILD_ID;

char* bcb_error_info = NULL;

void printError(uint16_t id) {
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

bool castNum(bcb_data data, int type, void* result) {
    uint64_t ndata = 0;
    long double fdata = 0;
    if (data.type >= BCB_TYPE_INT && data.type <= BCB_TYPE_U64) {
        if (type >= BCB_TYPE_FLOAT && type <= BCB_TYPE_LDOUBLE) {
            fdata = data.ndata;
        } else {
            ndata = data.ndata;
        }
    } else if (data.type >= BCB_TYPE_FLOAT && data.type <= BCB_TYPE_LDOUBLE) {
        if (type >= BCB_TYPE_INT && type <= BCB_TYPE_U64) {
            ndata = data.fdata;
        } else {
            fdata = data.fdata;
        }
    } else {
        return false;
    }
    switch (type) {
        case BCB_TYPE_INT:;
        case BCB_TYPE_UINT:;
            *((unsigned*)result) = (unsigned)ndata;
            break;
        case BCB_TYPE_BOOL:;
            *((bool*)result) = (bool)(ndata != 0);
            break;
        case BCB_TYPE_I8:;
        case BCB_TYPE_U8:;
            *((uint8_t*)result) = (uint8_t)ndata;
            break;
        case BCB_TYPE_I16:;
        case BCB_TYPE_U16:;
            *((uint16_t*)result) = (uint16_t)ndata;
            break;
        case BCB_TYPE_I32:;
        case BCB_TYPE_U32:;
            *((uint32_t*)result) = (uint32_t)ndata;
            break;
        case BCB_TYPE_I64:;
        case BCB_TYPE_U64:;
            *((uint64_t*)result) = (uint64_t)ndata;
            break;
        case BCB_TYPE_FLOAT:;
            *((float*)result) = (float)fdata;
            break;
        case BCB_TYPE_DOUBLE:;
            *((double*)result) = (double)fdata;
            break;
        case BCB_TYPE_LDOUBLE:;
            *((long double*)result) = (long double)fdata;
            break;
    }
    return true;
}

bool setNum(bcb_data data, int type, void* value) {
    if (data.type < BCB_TYPE_INT || data.type > BCB_TYPE_LDOUBLE) {
        return false;
    }
    uint64_t ndata = 0;
    long double fdata = 0;
    switch (type) {
        case BCB_TYPE_INT:;
        case BCB_TYPE_UINT:;
            ndata = *((unsigned*)value);
            break;
        case BCB_TYPE_BOOL:;
            ndata = (*((bool*)value) != 0);
            break;
        case BCB_TYPE_I8:;
        case BCB_TYPE_U8:;
            ndata = *((uint8_t*)value);
            break;
        case BCB_TYPE_I16:;
        case BCB_TYPE_U16:;
            ndata = *((uint16_t*)value);
            break;
        case BCB_TYPE_I32:;
        case BCB_TYPE_U32:;
            ndata = *((uint32_t*)value);
            break;
        case BCB_TYPE_I64:;
        case BCB_TYPE_U64:;
            ndata = *((uint64_t*)value);
            break;
        case BCB_TYPE_FLOAT:;
            fdata = *((float*)value);
            break;
        case BCB_TYPE_DOUBLE:;
            fdata = *((double*)value);
            break;
        case BCB_TYPE_LDOUBLE:;
            fdata = *((long double*)value);
            break;
    }
    if (data.type >= BCB_TYPE_INT && data.type <= BCB_TYPE_U64) {
        if (type >= BCB_TYPE_FLOAT && type <= BCB_TYPE_LDOUBLE) {
            data.ndata = fdata;
        } else {
            data.ndata = ndata;
        }
    } else if (data.type >= BCB_TYPE_FLOAT && data.type <= BCB_TYPE_LDOUBLE) {
        if (type >= BCB_TYPE_INT && type <= BCB_TYPE_U64) {
            data.ndata = fdata;
        } else {
            data.fdata = fdata;
        }
    }
    return true;
}

int main(int argc, char** argv) {
    printf("ByteCodeBASIC version %s %s (build %lu)\n", bcb_version, bcb_build, bcb_build_id);
    return 0;
}
