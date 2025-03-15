#ifndef BCBASIC_VLB_H
#define BCBASIC_VLB_H

#include <stddef.h>

#define BCB_VLB(T) {\
    T* data;\
    size_t len;\
    size_t size;\
}

#define BCB_VLB_OOM_NOP

#define BCB_VLB__EXP(b, en, ed, ...) do {\
    if ((b).len == (b).size) {\
        {\
            register size_t BCB_VLB__EXP__t = (b).size * en / ed;\
            if (BCB_VLB__EXP__t != (b).size) (b).size = BCB_VLB__EXP__t;\
            else ++(b).size;\
        }\
        void* BCB_VLB__EXP__t = realloc((b).data, (b).size * sizeof(*(b).data));\
        if (!BCB_VLB__EXP__t) {__VA_ARGS__}\
        (b).data = BCB_VLB__EXP__t;\
    }\
} while (0)

#define BCB_VLB_INIT(b, sz, ...) do {\
    (b).size = (sz);\
    (b).len = 0;\
    void* BCB_VLB_INIT__t = malloc((b).size * sizeof(*(b).data));\
    if (!BCB_VLB_INIT__t) {__VA_ARGS__}\
    (b).data = BCB_VLB_INIT__t;\
} while (0)
#define BCB_VLB_FREE(b) free((b).data)

#define BCB_VLB_ADD(b, d, en, ed, ...) do {\
    BCB_VLB__EXP((b), en, ed, __VA_ARGS__);\
    (b).data[(b).len++] = (d);\
} while (0)
#define BCB_VLB_NEXTPTR(b, o, en, ed, ...) do {\
    BCB_VLB__EXP((b), en, ed, __VA_ARGS__);\
    o = &(b).data[(b).len++];\
} while (0)

#define BCB_VLB_EXP(b, a, en, ed, ...) do {\
    (b).len += (a);\
    if ((b).len > (b).size) {\
        do {\
            register size_t BCB_VLB_EXP__t = (b).size * en / ed;\
            if (BCB_VLB_EXP__t != (b).size) (b).size = BCB_VLB_EXP__t;\
            else ++(b).size;\
        } while ((b).len > (b).size);\
        void* BCB_VLB_EXP__p = realloc((b).data, (b).size * sizeof(*(b).data));\
        if (!BCB_VLB_EXP__p) {__VA_ARGS__}\
        (b).data = BCB_VLB_EXP__p;\
    }\
} while (0)
#define BCB_VLB_SHRINK(b, ...) do {\
    if ((b).len != (b).size) {\
        (b).size = (b).len;\
        void* BCB_VLB_SHRINK__p = realloc((b).data, (b).size * sizeof(*(b).data));\
        if ((b).size && !BCB_VLB_SHRINK__p) {__VA_ARGS__}\
        (b).data = BCB_VLB_SHRINK__p;\
    }\
} while (0)

#endif
