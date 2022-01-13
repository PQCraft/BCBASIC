#ifndef BCB_COMMON_H
#define BCB_COMMON_H

#include <inttypes.h>
#include <stdio.h>

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
    BCB_ERR_NOT_PATH,           // No such file or directory
    BCB_ERR_IS_FILE,            // Is a file
    BCB_ERR_IS_DIR,             // Is a directory
    BCB_ERR_INVAL_CMD,          // Invalid command
    BCB_ERR_INVAL_FUNC,         // Invalid function
    BCB_ERR_INVAL_VAR,          // Invalid variable/array name
    BCB_ERR_INVAL_LABEL,        // Invalid label name
    BCB_ERR_MEMORY,             // Failed to allocate memory
    BCB_ERR_INTERNAL,           // Internal error
};

typedef struct {
    char* rawdata;      // Unsolved data string
    int type;           // Data type
    int dim;            // Array dimensions (0 for regular variable)
    int* size;          // Array dimension sizes
    void* pdata;        // Pointer data
    uint64_t ndata;     // 8-64-bit signed/unsigned int data
    long double fdata;  // 32-64/80-bit float data
} bcb_data;

typedef struct {
    char* name;     // Variable name
    bcb_data data;  // Variable data
} bcb_var;

typedef struct {
    int line;       // Line number in file
    int column;     // Column number in file
    char* linestr;  // String containing the line the command is on
    int id;         // Command ID
    int argc;       // Argument count
    bcb_data* args; // Arguments
} bcb_cmd;

typedef struct {
    FILE* file;     // File handle
    char* datablk;  // Data used by the file loader
    char* filename; // File name
    long filesize;  // Size of the file
    int linect;     // Line count of the file
    char** lines;   // Lines of the file
} bcb_preprog;

typedef struct {
    bcb_preprog* prog;  // Pointer to the preprocessed program the command is part of
    bcb_cmd* cmd;       // Command
} bcb_extcmd;

typedef struct {
    bcb_preprog* head;  // Pointer to the head preprocessed program
    int cmdct;          // Command count
    bcb_extcmd* cmds;   // Pointer to an array of commands
} bcb_prog;

typedef struct {
    void* next;     // Next linked command
    bcb_cmd* cmd;   // Command
} bcb_linked_cmd;

extern char* bcb_version;           // Compiled version
extern char* bcb_build;             // Compiled build
extern unsigned long bcb_build_id;  // Compiled build ID

#define nfree(ptr) {if (ptr) {free(ptr);} ptr = NULL;}          // Macro to free a pointer and set it to NULL
#define nfclose(file) {if (file) {fclose(file);} file = NULL;}  // Macro to close a file pointer and set it to NULL
#define swap(a, b) {__typeof__(a) c = a; a = b; b = c;}         // Macro to swap two variables using the type of the first variable

#endif
