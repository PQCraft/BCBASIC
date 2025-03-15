#ifndef BCBASIC_DEFS_H
#define BCBASIC_DEFS_H

// Allow redefinition of certain functions
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
#ifndef BCB_STRCMP
    #define BCB_STRCMP strcmp
#endif
#ifndef BCB_STRCASECMP
    #ifndef _WIN32
        #define BCB_STRCASECMP strcasecmp
    #else
        #define BCB_STRCASECMP stricmp
    #endif
#endif

#endif
