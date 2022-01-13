#ifndef BCB_MAIN_H
#define BCB_MAIN_H

#include <inttypes.h>
#include <stdbool.h>

#include "common.h"

void printError(uint16_t);                  // Print error message
void setErrorInfo(char*);                   // Set error info
bool getIntData(bcb_data*, int64_t*);       // Get signed numerical data out of a non-array bcb_data struct
bool getUintData(bcb_data*, uint64_t*);     // Get unsigned numerical data out of a non-array bcb_data struct
bool getFloatData(bcb_data*, long double*); // Get floating-point numerical data out of a non-array bcb_data struct
int isFile(char*);                          // Check if a path does not exist, is a file, or is a directory

extern uint16_t bcb_errno;      // Error number
extern char* bcb_error_info;    // Error info string

#endif
