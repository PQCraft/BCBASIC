#ifndef BCB_LOADER_H
#define BCB_LOADER_H

#include "common.h"

bcb_preprog* loadProgFile(char*);  // Load file and return an unparsed program
void freeProg(bcb_preprog*);       // Free a program handle

#endif
