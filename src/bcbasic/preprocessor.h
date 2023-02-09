#ifndef BCBASIC_PREPROCESSOR_H
#define BCBASIC_PREPROCESSOR_H

struct bcb_plineinfo {
    char* filename;
    char* pfilename;
    int line;
    int column;
};

struct bcb_pline {
    struct bcb_plines* next;
    //struct bcb_plines* prev;
    struct bcb_plineinfo info;
    char* data;
};

struct bcb_preprocessed {
    int lines;
    struct bcb_pline* headline;
    struct bcb_pline* linedata;
    int files;
    char** filenames;
};

#endif
