#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

#include "bcbasic.h"
#include "main.h"
#include "loader.h"

char* bcb_version = BCB_VERSION;
char* bcb_build = BCB_BUILD;
unsigned long bcb_build_id = BCB_BUILD_ID;

uint16_t bcb_errno = 0;
char* bcb_error_info = NULL;

uint64_t bcb_hashes[BCB_HASHES];

void printError(uint16_t id) {
    if (id == BCB_ERR_NONE) return;
    fprintf(stderr, "Error %u: ", id);
    switch (id) {
        default:;
            fputs("Unknown", stderr);
            break;
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
        case BCB_ERR_NOT_PATH:;
            fprintf(stderr, "No such file or directory: \"%s\"", bcb_error_info);
            break;
        case BCB_ERR_IS_FILE:;
            fprintf(stderr, "Is a file: \"%s\"", bcb_error_info);
            break;
        case BCB_ERR_IS_DIR:;
            fprintf(stderr, "Is a directory: \"%s\"", bcb_error_info);
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

void setErrorInfo(char* text) {
    nfree(bcb_error_info);
    bcb_error_info = strdup(text);
}

int isFile(char* path) {
    struct stat pathstat;
    if (stat(path, &pathstat)) return -1;
    return !(S_ISDIR(pathstat.st_mode));
}

uint64_t qhash(char* str, int max) {
    uint64_t hash = 0x7FBA0FC3DEADBEEF;
    uint16_t len = 0;
    int tmp;
    while ((max < 0 || len < max) && *str) {
        ++len;
        hash ^= ((*str) & 0xFF) * 0xF65C403B1034;
        for (int i = -1; i < ((*str) & 0x0F); ++i) {
            tmp = hash & 1;
            hash = ((uint64_t)tmp << 63) | (hash >> 1);
        }
        hash ^= (uint64_t)len * 0xE578E432;
        tmp = hash & 1;
        hash = ((uint64_t)tmp << 63) | (hash >> 1);
        ++str;
    }
    //hash ^= (uint64_t)len << 48;
    return hash;
}

int main(int argc, char** argv) {
    printf("ByteCodeBASIC version %s %s (build %lu)\n", bcb_version, bcb_build, bcb_build_id);
    if (argc > 1) {
        struct bcb_preprog* prog = loadProgFile(argv[1]);
        if (!prog) {
            printError(bcb_errno);
            return 1;
        }
        int linect = prog->linect;
        printf("%s (%ld bytes, %d line%c):\n", prog->filename, prog->filesize, linect, (linect == 1 ? 0 : 's'));
        for (long i = 0; i < linect; ++i) {
            printf("%5ld | %s\n", i + 1, prog->lines[i]);
        }
        freeProg(prog);
    }
    return 0;
}
