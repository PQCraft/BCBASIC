#ifndef BCBASIC_VMEXT_H
#define BCBASIC_VMEXT_H

// Replace the placeholder texts with #include directives for your custom built-in VM extensions

#ifdef BCB_VMEXTNAMES
    // Extension names in quotes with a comma following
    // Example:
    //     "myext",
    //     "otherext",
#endif

#ifdef BCB_VMEXT_GETNEXT_PRE
    // Run this before grabbing the next instruction
#endif
#ifdef BCB_VMEXT_GETNEXT_POST
    // Run this after grabbing the next instruction
#endif
#ifdef BCB_VMEXT_INST_ENUMS
    // Custom instruction enums. Use the BCB_VM_INSTCOUNT macro for the starting value, then redefine it to the number or enum name to be the new count.
#endif
#ifdef BCB_VMEXT_INST_CODE
    // Custom instruction cases. the following format is recommended:
    //     case ENUM: {
    //         // ...
    //     } break;
#endif

#endif
