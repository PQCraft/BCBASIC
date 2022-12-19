#ifndef BCB_COMMON_H
#define BCB_COMMON_H

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>

enum {  // Type IDs
    BCB_TYPE_VAR = -1;  // Variable
    BCB_TYPE_NONE,      // Uninitialized
    BCB_TYPE_NUMBER,    // Number
    BCB_TYPE_STRING,    // String
};

enum {  // Error IDs
    BCB_ERR_NONE,           // No error
    BCB_ERR_SYNTAX,         // Incorrect syntax
    BCB_ERR_TYPE_MM,        // Type mismatch
    BCB_ERR_DIM_MM,         // Dimension mismatch
    BCB_ERR_ARG_CT_MM,      // Argument count mismatch
    BCB_ERR_UNDEF_OP,       // Math operation resulted in undefined
    BCB_ERR_INVAL_DATA,     // Argument data invalid or out of range
    BCB_ERR_NOT_PATH,       // No such file or directory
    BCB_ERR_IS_FILE,        // Is a file
    BCB_ERR_IS_DIR,         // Is a directory
    BCB_ERR_INVAL_CMD,      // Invalid command
    BCB_ERR_INVAL_FUNC,     // Invalid function
    BCB_ERR_INVAL_VAR,      // Invalid variable/array name
    BCB_ERR_INVAL_LABEL,    // Invalid label name
    BCB_ERR_MEMORY,         // Failed to allocate memory
    BCB_ERR_INTERNAL,       // Internal error
};

enum {  // Global hashes
    BCB_HASH_EXIT,  // Hash for EXIT keyword
    BCB_HASH_QUIT,  // Hash for QUIT keyword
    BCB_HASH_PRINT, // Hash for PRINT keyword
    BCB_HASHES,     // Number of hashes
}

union bcb_data_stub {   // Data container
    long double num;    // Number data
    char* str;          // String data
    void* array;        // Array data
    bcb_data_stub* var; // Variable reference
};

struct bcb_data {   // Full data structure
    //char* rawdata;              // Unsolved data string
    uint8_t type;               // Data type
    int dim;                    // Array dimensions (0 for regular variable)
    int* size;                  // Array dimension sizes
    union bcb_data_stub data;   // Data
};

/*
struct bcb_var {    // Variable structure
    char* name;             // Variable name
    struct bcb_data data;   // Variable data
};
*/

struct bcb_arg {    // Argument structure
    uint64_t sep;           // Hash of char or word used to separate the argument
    struct bcb_data data;   // Argument data
};

struct bcb_cmd {    // Command structure
    int line;               // Line number in file
    int column;             // Column number in file
    uint64_t id;            // Command ID/hash
    int argc;               // Argument count
    struct bcb_arg argv;    // Arguments
};

struct bcb_preprog {    // Unprocessed program structure
    FILE* file;     // File handle
    char* datablk;  // Data used by the file loader
    char* filename; // File name
    long filesize;  // Size of the file
    int linect;     // Line count of the file
    char** lines;   // Lines of the file
};

struct bcb_extcmd { // Command structure with extended info
    struct bcb_preprog* prog;   // Pointer to the preprocessed program the command is part of
    struct bcb_cmd* cmd;        // Command
};

struct bcb_prog {   // Processed program structure
    struct bcb_preprog* head;   // Pointer to the head preprocessed program
    int cmdct;                  // Command count
    struct bcb_extcmd* cmds;    // Pointer to an array of commands
};

extern char* bcb_version;           // Compiled version
extern char* bcb_build;             // Compiled build
extern unsigned long bcb_build_id;  // Compiled build ID

#define nfree(ptr) {if (ptr) {free(ptr);} ptr = NULL;}          // Macro to free a pointer and set it to NULL
#define nfclose(file) {if (file) {fclose(file);} file = NULL;}  // Macro to close a file pointer and set it to NULL
#define swap(a, b) {__typeof__(a) c = a; a = b; b = c;}         // Macro to swap two variables using the type of the first variable

#endif
