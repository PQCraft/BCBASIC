#ifndef BCBASIC_PREPROCESSOR_H
#define BCBASIC_PREPROCESSOR_H

struct bcb_preprog_line {   // Preprocessed program line
    int filename;   // Index to file name/path in parent bcb_preprog struct
    int line;       // Line number in file
    char* text;     // Line text
};

struct bcb_preprog {    // Preprocessed program
    char** filenames;               // List of file names/paths
    struct bcb_preprog_line* lines; // Program lines
};

#endif
