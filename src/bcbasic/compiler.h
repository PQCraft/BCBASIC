#ifndef BCBASIC_COMPILER_H
#define BCBASIC_COMPILER_H

#include "interpreter.h"

typedef int (*bcb_extcall_t)(struct bcb_state* /*state*/, int /*command id*/);

struct bcb_command {    // Command
    int line;       // Line
    int col;        // Column
    int filename;   // Index to file name/path in parent bcb_program struct
    uint16_t group; // Command group
    uint16_t id;    // Command id
};

struct bcb_program {    // Program
    int commandct;                  // Command count
    struct bcb_command* commands;   // Commands
    int extct;                      // Extension count
    bcb_extcall_t* extcall;         // Extension function calls
};

#endif
