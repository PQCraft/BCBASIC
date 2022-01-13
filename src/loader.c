#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "loader.h"
#include "main.h"

bcb_preprog* loadProgFile(char* name) {
    int filestat = isFile(name);
    if (!filestat) {
        bcb_errno = BCB_ERR_IS_DIR;
        setErrorInfo(name);
        return NULL;
    } else if (filestat != 1) {
        bcb_errno = BCB_ERR_NOT_PATH;
        setErrorInfo(name);
        return NULL;
    }
    FILE* file = fopen(name, "r");
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    char* data = malloc(size + 1);
    fseek(file, 0, SEEK_SET);
    long i = 0;
    while (i < size && !feof(file)) {
        int tmpc = fgetc(file);
        if (tmpc < 0) tmpc = 0;
        data[i++] = (char)tmpc;
    }
    data[i] = 0;
    bcb_preprog* prog = calloc(1, sizeof(bcb_preprog));
    if (!prog) {bcb_errno = BCB_ERR_MEMORY; return NULL;}
    prog->file = file;
    prog->datablk = data;
    prog->filename = strdup(name);
    prog->filesize = size;
    int linect = 0;
    for (long i = 0; i <= size; ++i) {
        if (!data[i] || data[i] == '\n') ++linect;
    }
    if (linect > 0 && ((size > 1 && data[size - 1] == '\n' && !data[size]) || size == 0)) linect--;
    prog->linect = linect;
    char** lines = malloc(linect * sizeof(char*));
    int offset = 0;
    linect = 0;
    for (long i = 0; i <= size; ++i) {
        if (!data[i] || data[i] == '\n') {
            data[i] = 0;
            if (linect < prog->linect) lines[linect++] = data + offset;
            offset = i + 1;
        }
    }
    prog->lines = lines;
    return prog;
}

void freeProg(bcb_preprog* prog) {
    nfclose(prog->file);
    nfree(prog->datablk);
    nfree(prog->filename);
    nfree(prog->lines);
    nfree(prog);
}
