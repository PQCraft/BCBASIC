#define BCBASIC_STATIC

#include "vm.h"

static const char* const extnames[] = {
    #define BCB_VMEXTNAMES
    #include "user/vmext.h"
    #undef BCB_VMEXTNAMES
    NULL
};
static const size_t extcount = sizeof(extnames) / sizeof(*extnames) - 1;

const char* const* BCB_VM_GetExtensions(size_t* count) {
    if (count) *count = extcount;
    return extnames;
}
