#ifndef BCB_COMMON_H
#define BCB_COMMON_H

#include <inttypes.h>

enum {
    BCB_TYPE_NONE = -1, // Used for empty arguments
    BCB_TYPE_INT,       // Singed 32/64-bit (platform dependent)
    BCB_TYPE_UINT,      // Unsigned 32/64-bit (platform dependent)
    BCB_TYPE_BOOL,      // Boolean 1-bit
    BCB_TYPE_I8,        // Signed 8-bit
    BCB_TYPE_I16,       // Signed 16-bit
    BCB_TYPE_I32,       // Signed 32-bit
    BCB_TYPE_I64,       // Signed 64-bit
    BCB_TYPE_U8,        // Unsigned 8-bit
    BCB_TYPE_U16,       // Unsigned 16-bit
    BCB_TYPE_U32,       // Unsigned 32-bit
    BCB_TYPE_U64,       // Unsigned 64-bit
    BCB_TYPE_FLOAT,     // Float 32-bit
    BCB_TYPE_DOUBLE,    // Float 64-bit
    BCB_TYPE_LDOUBLE,   // Float 64/80-bit (platform dependent)
    BCB_TYPE_STRING,    // String
};

enum {
    BCB_ERR_NONE,               // No error
    BCB_ERR_SYNTAX,             // Incorrect syntax
    BCB_ERR_TYPE_MM,            // Type mismatch
    BCB_ERR_DIM_MM,             // Dimension mismatch
    BCB_ERR_ARG_CT_MM,          // Argument count mismatch
    BCB_ERR_UNDEF_OP,           // Math operation resulted in undefined
    BCB_ERR_INVAL_DATA,         // Argument data invalid or out of range
    BCB_ERR_NO_FILE,            // No such file
    BCB_ERR_NO_DIR,             // No such directory
    BCB_ERR_NO_FD,              // No such file or directory
    BCB_ERR_NOT_FILE,           // Not a file
    BCB_ERR_NOT_DIR,            // Not a directory
    BCB_ERR_INVAL_CMD,          // Invalid command
    BCB_ERR_INVAL_FUNC,         // Invalid function
    BCB_ERR_INVAL_VAR,          // Invalid variable/array name
    BCB_ERR_INVAL_LABEL,        // Invalid label name
    BCB_ERR_MEMORY,             // Failed to allocate memory
    BCB_ERR_CUSTOM = 65535,     // Custom error (for use by extensions)
};

extern char* bcb_error_info;    // Error info string

typedef struct {
    int type;           // Data type
    int dim;            // Array dimensions (0 for regular variable)
    void* pdata;        // Pointer data
    uint64_t ndata;     // 8-64-bit signed/unsigned int data
    long double fdata;  // 32-64/80-bit float data
} bcb_data;

typedef struct {
    char* name;     // Variable name
    bcb_data data;  // Variable data
} bcb_var;

extern char* bcb_version;           // Compiled version
extern char* bcb_build;             // Compiled build
extern unsigned long bcb_build_id;  // Compiled build ID

#endif
