#ifndef BCB_LOADER_H
#define BCB_LOADER_H

#include "common.h"

struct bcb_preprog* loadProgFile(char*);  // Load file and return an unparsed program
void freeProg(struct bcb_preprog*);       // Free a program handle

#endif
