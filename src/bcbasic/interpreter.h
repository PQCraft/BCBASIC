#ifndef BCBASIC_INTERPRETER_H
#define BCBASIC_INTERPRETER_H

struct bcb_argstack {   // Argument stack
    int size;               // Number of arguments allocated
    int argc;               // Amount of arguments held in .argv
    struct bcb_data* argv;  // Argument data
};

struct bcb_thread {
    int state; // Interpreter state
};

enum {
    BCB_STATE_HALTED,
    BCB_STATE_ACTIVE,
    BCB_STATE_PAUSED,
};

struct bcb_state {  // Interpreter state
    // Program state
    int prog;                       // Current program
    struct bcb_program* progstack;  // Program stack
    int* pc;                        // Program counters (current command)
    // Variables
    int varct;                      // Variable count
    struct bcb_var* vars;           // Variable data
    int structct;                   // Struct definition count
    struct bcb_struct* structs;     // Struct definitions
    int unionct;                    // Union definition count
    struct bcb_union* unions;       // Union definitions
    // Temporary data
    struct bcb_data funcret;        // Return value of last function
    int argstacksize;               // Number of argument stacks allocated
    int argstackindex;              // Current argument stack
    struct bcb_argstack* argstack;  // Argument stacks
};

#endif
