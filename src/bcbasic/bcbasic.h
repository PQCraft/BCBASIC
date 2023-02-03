/* .------------------------------------------------------------------------. */
/* |                          BCBASIC main header                           | */
/* '------------------------------------------------------------------------' */
/*                                                                            */
/*  Command IDs:                                                              */
/*                                                                            */
/*    Commands have 32-bit IDs: [16 bits: Group][16 bits: ID #]               */
/*                                                                            */
/*    - Group ID 0 is reserved for internal actions (program flow, changing   */
/*      state variables, arithmetic operations, etc).                         */
/*    - Group ID 1 is reserved for built-in commands and functions.           */
/*    - Group IDs 2 and up are for extensions.                                */
/*                                                                            */
/* '------------------------------------------------------------------------' */

#ifndef BCBASIC_BCBASIC_H
#define BCBASIC_BCBASIC_H

// Version (BCB_VER_MAJOR.BCB_VER_MINOR.BCB_VER_PATCH)
#define BCB_VER_MAJOR 0
#define BCB_VER_MINOR 0
#define BCB_VER_PATCH 0

// Allow redefinition of certain functions
#ifndef BCB_MALLOC
    #define BCB_MALLOC malloc
#endif
#ifndef BCB_CALLOC
    #define BCB_CALLOC calloc
#endif
#ifndef BCB_REALLOC
    #define BCB_REALLOC realloc
#endif
#ifndef BCB_FREE
    #define BCB_FREE free
#endif
#ifndef BCB_STRDUP
    #define BCB_STRDUP strdup
#endif
#ifndef BCB_MEMSET
    #define BCB_MEMSET memset
#endif
#ifndef BCB_MEMCPY
    #define BCB_MEMCPY memcpy
#endif
#ifndef BCB_REALPATH
    #ifndef _WIN32
        #define BCB_REALPATH(x, y) realpath(x, y)
    #else
        #define BCB_REALPATH(x, y) _fullpath(y, x, MAX_PATH)
    #endif
#endif

// Required includes
#include <inttypes.h>
#include <stdlib.h>
#include <sys/stat.h>

enum {  // Error codes
    BCB_ERR_NONE,       // No error
    BCB_ERR_SYNTAX,     // Syntax error
    BCB_ERR_TYPE,       // Type mismatch
    BCB_ERR_ARG,        // Incorrect argument count
    BCB_ERR_INVALDATA,  // Invalid data
    BCB_ERR_INVALNAME,  // Invalid name
    BCB_ERR_NOTPATH,    // No such file or directory
    BCB_ERR_NOTFILE,    // Expected a file
    BCB_ERR_NOTDIR,     // Expected a directory
    BCB_ERR_MEMORY,     // Allocation failure
    BCB_ERR_EXTENSION,  // Failed to load an extension
    BCB_ERR_INTERNAL,   // Internal error
};

struct bcb_var {    // Variable
    char* name;             // Variable name
    struct bcb_data* value; // Variable data
};

struct bcb_struct { // Struct info
    int elemct;             // Number of elements
    struct bcb_type* type;  // Types
    unsigned long size;     // Total size of struct
    unsigned long* stride;  // Sizes of individual elements
};

struct bcb_union { // Union info
    int elemct;             // Number of elements
    struct bcb_type* type;  // Types
    unsigned long size;     // Total size of union
};

struct bcb_string { // String
    int size;   // Size of .data (incl. \0)
    int len;    // String length (not incl. \0)
    char* data; // String text
};

enum {  // Type IDs
    BCB_TYPE_NONE,      // Used for skipped arguments
    BCB_TYPE_VAR,       // Variable reference
    BCB_TYPE_STRUCT,    // Struct
    BCB_TYPE_UNION,     // Union
    BCB_TYPE_STRING,    // String
    BCB_TYPE_INT,       // Integer
    BCB_TYPE_UINT,      // Unsigned integer
    BCB_TYPE_CHAR,      // Char
    BCB_TYPE_UCHAR,     // Unsigned char
    BCB_TYPE_SINT,      // Short integer
    BCB_TYPE_SUINT,     // Short unsigned integer
    BCB_TYPE_LINT,      // Long integer
    BCB_TYPE_LUINT,     // Long unsigned integer
    BCB_TYPE_LLINT,     // Long long integer
    BCB_TYPE_LLUINT,    // Long long unsigned integer
    BCB_TYPE_I8,        // 8-bit integer
    BCB_TYPE_U8,        // 8-bit unsigned integer
    BCB_TYPE_I16,       // 16-bit integer
    BCB_TYPE_U16,       // 16-bit unsigned integer
    BCB_TYPE_I32,       // 32-bit integer
    BCB_TYPE_U32,       // 32-bit unsigned integer
    BCB_TYPE_I64,       // 64-bit integer
    BCB_TYPE_U64,       // 64-bit unsigned integer
    BCB_TYPE_FLOAT,     // Float
    BCB_TYPE_LFLOAT,    // Double
    BCB_TYPE_LLFLOAT,   // Long double
};

struct bcb_type {   // Type
    uint8_t id;     // Type ID
    int index;      // Type index
    uint8_t dim;    // Array dimensions (0 if not an array)
    int* sizes;     // Dimension sizes
};

struct bcb_data {   // Data
    struct bcb_type type;   // Type info
    void* data;             // Data
};

// Include individual sections
#include "preprocessor.h"
#include "compiler.h"
#include "interpreter.h"
#include "io.h"

#endif
