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

// Allow redefinition of memory management functions
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

#include <inttypes.h>

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

struct bcb_preprog_line {   // Preprocessed program line
    int filename;   // Index to file name/path in parent bcb_preprog struct
    int line;       // Line number in file
    char* text;     // Line text
};

struct bcb_preprog {    // Preprocessed program
    char** filenames;               // List of file names/paths
    struct bcb_preprog_line* lines; // Program lines
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

struct bcb_command {    // Command
    int line;       // Line
    int col;        // Column
    int filename;   // Index to file name/path in parent bcb_program struct
    uint16_t group; // Command group
    uint16_t id;    // Command id
};

struct bcb_state; // Suppress the "declared inside parameter" error below
typedef int (*bcb_extcall_t)(struct bcb_state* /*state*/, int /*command id*/);

struct bcb_program {    // Program
    int commandct;                  // Command count
    struct bcb_command* commands;   // Commands
    int extct;                      // Extension count
    bcb_extcall_t* extcall;         // Extension function calls
};

struct bcb_argstack {   // Argument stack
    int size;               // Number of arguments allocated
    int argc;               // Amount of arguments held in .argv
    struct bcb_data* argv;  // Argument data
};

enum {
    BCB_STATE_HALTED,
    BCB_STATE_ACTIVE,
    BCB_STATE_PAUSED,
};

struct bcb_state {  // Interpreter state
    // Program state
    int state;                      // Interpreter state
    int prog;                       // Current program
    struct bcb_program* progstack;  // Program stack
    int* pc;                        // Program counters (current command)
    // Variables
    int varct;                      // Variable count
    struct bcb_var* vars;           // Variable data
    int structct;                   // Struct definition count
    struct bcb_struct* structs;     // Struct definitions
    int unionct;                    // Union definition count
    struct bcb_union* unions;       // Union definitions
    // Temporary data
    struct bcb_data funcret;        // Return value of last function
    int argstacksize;               // Number of argument stacks allocated
    int argstackindex;              // Current argument stack
    struct bcb_argstack* argstack;  // Argument stacks
};

#endif
