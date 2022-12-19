#include "bcbasic.h"
#include "interp.h"
#include "main.h"

int parsecmd(char* str, struct bcb_cmd* cmd) {
    while (*str == ' ' || *str == '\t') ++str;
    int i = 0;
    char tmpc = str[0];
    switch (tmpc) {
        case '?':;
            cmd->id = bcb_hashes[BCB_HASH_PRINT];
            break;
        default:;
            while (str[i] && str[i] != ' ') ++i;
            cmd->id = qhash(str, i);
            break;
    }
    
}
