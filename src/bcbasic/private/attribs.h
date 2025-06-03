#ifndef BCBASIC_ATTRIBS_H
#define BCBASIC_ATTRIBS_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _MSC_VER
    #define BCB_PACKEDENUM enum __attribute__((packed))
    #define BCB_ALWAYSINLINE inline __attribute__((always_inline))
    #define BCB_THREADLOCAL __thread
#else
    #define BCB_PACKEDENUM enum
    #define BCB_ALWAYSINLINE __forceinline
    #define BCB_THREADLOCAL __declspec(thread)
#endif

#ifdef __cplusplus
}
#endif

#endif
