#ifndef BCBASIC_INTERPRETER_H
#define BCBASIC_INTERPRETER_H

struct bcb_thread {
    int program;
    struct bcb_compiled* programdata;
};

struct bcb_state {
    int threads;
    struct bcb_thread* threaddata;
};

#endif
