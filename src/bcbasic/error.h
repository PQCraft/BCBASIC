#ifndef BCBASIC_ERROR_H
#define BCBASIC_ERROR_H

#ifdef __cplusplus
extern "C" {
#endif

enum BCB_Error {    // Error codes
    BCB_ERROR_NONE,         // No error
    BCB_ERROR_SYNTAX,       // Syntax error
    BCB_ERROR_TYPE,         // Type mismatch
    BCB_ERROR_INVALNAME,    // Invalid name
    BCB_ERROR_INVALARGC,    // Invalid argument count
    BCB_ERROR_STALEREF,     // Stale reference
    BCB_ERROR_MEMORY,       // Allocation failure
    BCB_ERROR_INTERNAL,     // Internal error
};

const char* BCB_GetErrorName(enum BCB_Error);
const char* BCB_GetErrorDesc(enum BCB_Error);

#ifdef __cplusplus
}
#endif

#endif
