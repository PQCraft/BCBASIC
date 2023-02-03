#include "bcbasic.h"
#include "io.h"

#include <stddef.h>
#include <stdio.h>

int _bcb_isFile(char* path) {
    if (!path || !(*path)) return -1; // Return -1 if obviously invalid
    struct stat pathstat;
    if (stat(path, &pathstat)) return -1; // Consider file to not exist if stat fails
    if (S_ISLNK(pathstat.st_mode)) { // Check for a link
        int ret = -1; // Return -1 by default (if realpath fails)
        path = BCB_REALPATH(path, NULL); // Follow link
        if (path != NULL) { // Find status of actual path
            ret = _bcb_isFile(path);
            free(path);
        }
        return ret;
    }
    if (S_ISDIR(pathstat.st_mode)) return 0; // Return 0 if a dir
    if (S_ISREG(pathstat.st_mode)) return 1; // Return 1 if a file
    return 2; // Return 2 for everything else
}

struct _bcb_filedata* _bcb_loadFile(char* path) {
    if (_bcb_isFile(path) != 1) return NULL; // Fail if not a regular file
    FILE* file = fopen(path, "r"); // Open file to read
    if (!file) return NULL; // Fail if file can't be opened
    struct _bcb_filedata* ret = BCB_MALLOC(sizeof(*ret)); // Allocate filedata struct
    fseek(file, 0, SEEK_END);
    ret->size = ftell(file); // Get size of file
    fseek(file, 0, SEEK_SET);
    ret->data = BCB_MALLOC(ret->size);
    fread(ret->data, 1, ret->size, file); // Read in file data
    fclose(file); // Close file
    return ret;
}

void _bcb_freeFile(struct _bcb_filedata* file) {
    BCB_FREE(file->data);
    BCB_FREE(file);
}
