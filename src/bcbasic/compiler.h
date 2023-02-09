#ifndef BCBASIC_COMPILER_H
#define BCBASIC_COMPILER_H

#include <inttypes.h>
#include <stdbool.h>

struct bcb_command {
    int16_t gid;
    uint16_t id;
    int argc;
    void** argv;
};

struct bcb_compiled {
    int commands;
    struct bcb_command* commanddata;
};

struct bcb_extinfo {
    bool external;
    char* name;
    void* init;
};

struct bcb_compileropt {
    struct bcb_extinfo* extensions;
    void* findext;
    int optimization;
};

#endif
