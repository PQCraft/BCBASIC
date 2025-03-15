#ifndef BCBASIC_COMPILER_H
#define BCBASIC_COMPILER_H

#include <stdint.h>
#include <stddef.h>
#include "error.h"

struct BCB_PreprocMacro {
    char* name;
    char* value;
    uint32_t namecrc;
};

// Fills in the CRC values of the 'name' members
void BCB_PrepPreprocMacros(struct BCB_PreprocMacro*, size_t ct);

struct BCB_CompilerOpt {
    size_t macroct;
    struct BCB_PreprocMacro* macros;
};

// Callback type for the compiler to request program text
// Return a pointer to the text and write the length to the len param, or return NULL when out of data
typedef char* (*BCB_CompilerGetText)(void* userdata, size_t* len);

struct BCB_Script;

enum BCB_Error BCB_Compile(BCB_CompilerGetText in, void* userdata, struct BCB_CompilerOpt*, struct BCB_Script* out);

#endif
