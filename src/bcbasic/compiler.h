#ifndef BCBASIC_COMPILER_H
#define BCBASIC_COMPILER_H

#include <stdint.h>
#include <stddef.h>
#include "error.h"

// Macros
enum BCB_MacroDefType {
    BCB_MACRODEF_OBJLIKE,   // Object-like macro
    BCB_MACRODEF_FUNCLIKE   // Function-like macro
};
struct BCB_MacroDef {
    enum BCB_MacroDefType type;
    char* name;
    uint32_t namecrc;
    union {
        struct {
            char* text;
        } objlike;
        struct {
            struct {
                size_t count;
                char* names;
            } args;
            char* text;
        } funclike;
    };
};

// Validates names and fills in CRC values
int BCB_PrepMacroDefs(struct BCB_MacroDef*, size_t count, unsigned flags);
#define BCB_PREPMACRODEFS_SKIPVALIDATION (1 << 0)   // Skip validating names if you already know they are valid

// Get a list of extensions the compiler supports
char** BCB_GetCompilerExtensions(void);

// Compiler options
struct BCB_CompilerOpt {
    struct {
        struct BCB_MacroDef* data;
        size_t count;
    } macros;
    struct {
        char** claim;       // Claim these extensions are available (NULL to use 'enable' and 'ondemand')
        char** enable;      // Enable these extensions
        char** ondemand;    // Enable these extensions only if `#require`d
    } extensions;
};

// Callback type for the compiler to request program text
// Return a pointer to the text and write the length to the len param, or return NULL when out of data
typedef char* (*BCB_CompilerGetText)(void* userdata, size_t* len);

struct BCB_Script;

enum BCB_Error BCB_Compile(BCB_CompilerGetText in, void* userdata, struct BCB_CompilerOpt*, struct BCB_Script* out);

#endif
