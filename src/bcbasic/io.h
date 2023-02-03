#ifndef BCBASIC_IO_H
#define BCBASIC_IO_H

struct _bcb_filedata {  // File data struct
    long size;              // File size
    unsigned char* data;    // File data
};

// Checks if a path is a file
// [in] path: File path
// Returns -1 if not found, 0 for a dir, 1 for a file, and 2 for anything else
int _bcb_isFile(char* /*path*/);

// Reads a file into a struct _bcb_filedata
// [in] path: File path
// Returns a pointer to a struct _bcb_filedata
struct _bcb_filedata* _bcb_loadFile(char* /*path*/);

// Frees a struct _bcb_filedata
// [in] file: struct _bcb_filedata pointer given by _bcb_loadFile
void _bcb_freeFile(struct _bcb_filedata* /*file*/);

// Displays a prompt (pass NULL for no prompt)
/* [in, optional] prompt: Prompt to display (enclose hidden text in \x01 and
                          \x02 and use \x01\x01 or \x02\x02 to print \x01 or
                          \x02) */
// [in]           column: Column the cursor is currently on
// Returns a char* string containing the text entered or NULL if cancelled
char* _bcb_prompt(char* /*prompt*/, int /*column*/);

#endif
