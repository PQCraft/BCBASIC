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
#ifndef BCB_STRCMP
    #define BCB_STRCMP strcmp
#endif
#ifndef BCB_STRCASECMP
    #ifndef _WIN32
        #define BCB_STRCASECMP strcasecmp
    #else
        #define BCB_STRCASECMP stricmp
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

enum {  // Type groups
    BCB_TYPEGROUP_NONE,     // Used for skipped arguments
    BCB_TYPEGROUP_REGULAR,  // Regular data (single-type single-offset data)
    BCB_TYPEGROUP_STRUCT,   // Struct (multi-type multi-offset data)
    BCB_TYPEGROUP_UNION,    // Union (multi-type single-offset data)
    BCB_TYPEGROUP_VARREF,   // Variable reference
};

enum {  // Type IDs
    BCB_TYPEID_STRING,    // String
    BCB_TYPEID_INT,       // Integer
    BCB_TYPEID_UINT,      // Unsigned integer
    BCB_TYPEID_CHAR,      // Char
    BCB_TYPEID_UCHAR,     // Unsigned char
    BCB_TYPEID_SINT,      // Short integer
    BCB_TYPEID_SUINT,     // Short unsigned integer
    BCB_TYPEID_LINT,      // Long integer
    BCB_TYPEID_LUINT,     // Long unsigned integer
    BCB_TYPEID_LLINT,     // Long long integer
    BCB_TYPEID_LLUINT,    // Long long unsigned integer
    BCB_TYPEID_I8,        // 8-bit integer
    BCB_TYPEID_U8,        // 8-bit unsigned integer
    BCB_TYPEID_I16,       // 16-bit integer
    BCB_TYPEID_U16,       // 16-bit unsigned integer
    BCB_TYPEID_I32,       // 32-bit integer
    BCB_TYPEID_U32,       // 32-bit unsigned integer
    BCB_TYPEID_I64,       // 64-bit integer
    BCB_TYPEID_U64,       // 64-bit unsigned integer
    BCB_TYPEID_FLOAT,     // Float
    BCB_TYPEID_LFLOAT,    // Double
    BCB_TYPEID_LLFLOAT,   // Long double
};

struct bcb_type {   // Type info struct
    int group;      // Type group
    union {
        int index;  // Struct/union definition or variable index
        int id;     // Type ID for regular type
    };
    long offset;    // Variable reference offset in struct
    int dim;        // Array dimensions (0 if not an array)
    long* sizes;    // Sizes of each dimension
};

struct bcb_structelem {
    struct bcb_type type;
    char* name;
    long offset;
};

struct bcb_structdef {
    int elements;
    struct bcb_structelem* elemdata;
    long size;
};

struct bcb_unionelem {
    struct bcb_type type;
    char* name;
};

struct bcb_uniondef {
    int elements;
    struct bcb_unionelem* elemdata;
    long size;
};

struct bcb_string {
    unsigned size;
    unsigned length;
    char* data;
};

// Include individual sections
#include "preprocessor.h"
#include "compiler.h"
#include "interpreter.h"
#include "io.h"

#endif
