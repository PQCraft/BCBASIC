#ifndef BCBASIC_VM_H
#define BCBASIC_VM_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

// Returns a NULL-terminated list of the extensions the VM has, and optionally outputs the count
char** BCB_VM_GetExtensions(size_t* count);

#ifdef BCBASIC_STATIC

// ...

#endif

#ifdef __cplusplus
}
#endif

#endif
