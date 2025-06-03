#ifndef BCBASIC_VLB_H
#define BCBASIC_VLB_H

#include <stddef.h>
#include <stdlib.h>

#include "defs.h"

#define BCB_VLB(T) {\
    T* data;\
    size_t len;\
    size_t size;\
}

#define BCB_VLB_OOM_NOP

#define BCB_VLB__EXP(BCB_VLB__b, BCB_VLB__en, BCB_VLB__ed, BCB_VLB__do, ...) do {\
    if ((BCB_VLB__b).len != (BCB_VLB__b).size) {\
        BCB_VLB__do;\
    } else {\
        register size_t BCB_VLB__tmp = (BCB_VLB__b).size;\
        BCB_VLB__tmp = BCB_VLB__tmp * (BCB_VLB__en) / (BCB_VLB__ed);\
        if (BCB_VLB__tmp == (BCB_VLB__b).size) ++BCB_VLB__tmp;\
        void* BCB_VLB__ptr = BCB_REALLOC((BCB_VLB__b).data, BCB_VLB__tmp * sizeof(*(BCB_VLB__b).data));\
        if (BCB_VLB__ptr) {(BCB_VLB__b).data = BCB_VLB__ptr; BCB_VLB__do; (BCB_VLB__b).size = BCB_VLB__tmp;}\
        else {__VA_ARGS__}\
    }\
} while (0)
#define BCB_VLB__EXP_MULTI(BCB_VLB__b, BCB_VLB__l, BCB_VLB__en, BCB_VLB__ed, ...) do {\
    if ((BCB_VLB__l) > (BCB_VLB__b).size) {\
        register size_t BCB_VLB__tmp = (BCB_VLB__b).size;\
        do {\
            register size_t BCB_VLB__old = BCB_VLB__tmp;\
            BCB_VLB__tmp = BCB_VLB__tmp * (BCB_VLB__en) / (BCB_VLB__ed);\
            if (BCB_VLB__tmp == BCB_VLB__old) ++BCB_VLB__tmp;\
        } while (BCB_VLB__tmp < (BCB_VLB__l));\
        void* BCB_VLB__ptr = BCB_REALLOC((BCB_VLB__b).data, BCB_VLB__tmp * sizeof(*(BCB_VLB__b).data));\
        if (BCB_VLB__ptr) {(BCB_VLB__b).data = BCB_VLB__ptr; (BCB_VLB__b).len = (BCB_VLB__l); (BCB_VLB__b).size = BCB_VLB__tmp;}\
        else {__VA_ARGS__}\
    } else if ((BCB_VLB__l) > (BCB_VLB__b).len) {\
        (BCB_VLB__b).len = (BCB_VLB__l);\
    }\
} while (0)

#define BCB_VLB_INIT(BCB_VLB__b, BCB_VLB__sz, ...) do {\
    (BCB_VLB__b).data = BCB_MALLOC((BCB_VLB__sz) * sizeof(*(BCB_VLB__b).data));\
    (BCB_VLB__b).len = 0;\
    if ((BCB_VLB__sz) && (BCB_VLB__b).data) (BCB_VLB__b).size = (BCB_VLB__sz);\
    else {(BCB_VLB__b).size = 0; {__VA_ARGS__}}\
} while (0)
#define BCB_VLB_FREE(b) BCB_FREE((b).data)

#define BCB_VLB_ADD(BCB_VLB__b, BCB_VLB__d, BCB_VLB__en, BCB_VLB__ed, ...) do {\
    BCB_VLB__EXP((BCB_VLB__b), (BCB_VLB__en), (BCB_VLB__ed), (BCB_VLB__b).data[(BCB_VLB__b).len++] = (BCB_VLB__d), __VA_ARGS__);\
} while (0)
#define BCB_VLB_NEXTPTR(BCB_VLB__b, BCB_VLB__o, BCB_VLB__en, BCB_VLB__ed, ...) do {\
    BCB_VLB__EXP((BCB_VLB__b), (BCB_VLB__en), (BCB_VLB__ed), (BCB_VLB__o) = &(BCB_VLB__b).data[(BCB_VLB__b).len++], __VA_ARGS__);\
} while (0)

#define BCB_VLB_EXPAND(BCB_VLB__b, BCB_VLB__a, BCB_VLB__en, BCB_VLB__ed, ...) do {\
    register size_t BCB_VLB__l = (BCB_VLB__b).len + (BCB_VLB__a);\
    BCB_VLB__EXP_MULTI((BCB_VLB__b), (BCB_VLB__l), (BCB_VLB__en), (BCB_VLB__ed), __VA_ARGS__);\
} while (0)
#define BCB_VLB_EXPANDTO(BCB_VLB__b, BCB_VLB__l, BCB_VLB__en, BCB_VLB__ed, ...) do {\
    BCB_VLB__EXP_MULTI((BCB_VLB__b), (BCB_VLB__l), (BCB_VLB__en), (BCB_VLB__ed), __VA_ARGS__);\
} while (0)
#define BCB_VLB_SHRINK(BCB_VLB__b, ...) do {\
    if ((BCB_VLB__b).len != (BCB_VLB__b).size) {\
        void* BCB_VLB__ptr = BCB_REALLOC((BCB_VLB__b).data, (BCB_VLB__b).len * sizeof(*(BCB_VLB__b).data));\
        if (BCB_VLB__ptr || !(BCB_VLB__b).len) {(BCB_VLB__b).data = BCB_VLB__ptr; (BCB_VLB__b).size = (BCB_VLB__b).len;}\
        else {__VA_ARGS__}\
    }\
} while (0)

#endif
