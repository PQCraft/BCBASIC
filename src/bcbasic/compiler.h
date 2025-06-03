#ifndef BCBASIC_COMPILER_H
#define BCBASIC_COMPILER_H

#include "error.h"
#ifdef BCBASIC_STATIC
    #include "private/vlb.h"
    #include "private/attribs.h"
#endif
#ifndef BCBASIC_NOSTDIO
    #include <stdio.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>

// --- Some forward-decls ---

// Compiler state
struct BCB_Compiler;

// --- Text streams ---

// Stack of text stream sources for the compiler to read in a program
struct BCB_Compiler_TextStream;

// Called when more data is needed (req >= 1) or when closing and freeing the source (req = 0)
//   Writes out no more than 'req' chars and returns the amount written
//   The source index is provided to the 'index' param
typedef size_t (*BCB_Compiler_TextStream_DataCallback)(size_t index, void* userdata, size_t req, char* out);
// Called when the source is closed
//   The source index is provided to the 'index' param
typedef size_t (*BCB_Compiler_TextStream_CloseCallback)(size_t index, void* userdata);

// Allocate and init a new stream stack. Returns NULL on error
struct BCB_Compiler_TextStream* BCB_Compiler_TextStream_New(void);
// Deinit and free a stream stack
void BCB_Compiler_TextStream_Delete(struct BCB_Compiler_TextStream*);

// Pushes a new stream onto the stack
//   Returns an index on success and (size_t)-1 on failure
size_t BCB_Compiler_TextStream_OpenMemory(struct BCB_Compiler_TextStream*, char* name, const char* data, size_t len,
                                          BCB_Compiler_TextStream_CloseCallback, void* userdata);
size_t BCB_Compiler_TextStream_OpenCallback(struct BCB_Compiler_TextStream*, char* name, BCB_Compiler_TextStream_DataCallback cb,
                                            BCB_Compiler_TextStream_CloseCallback, void* userdata);
#ifndef BCBASIC_NOSTDIO
size_t BCB_Compiler_TextStream_OpenFile(struct BCB_Compiler_TextStream*, char* name, FILE* file, BCB_Compiler_TextStream_CloseCallback, void* userdata);
size_t BCB_Compiler_TextStream_OpenFileDesc(struct BCB_Compiler_TextStream*, char* name, int fd, BCB_Compiler_TextStream_CloseCallback, void* userdata);
#endif
// Closes the top stream in the stack
void BCB_Compiler_TextStream_Close(struct BCB_Compiler_TextStream*);

// Returns the next char as unsigned char or returns -1 when all sources have ended
int BCB_Compiler_TextStream_GetChar(struct BCB_Compiler_TextStream*);
// Sets the unget flag which makes the last char return again
void BCB_Compiler_TextStream_SetUnget(struct BCB_Compiler_TextStream*);

// --- Extensions ---

// Generic callback when no extra params need to be given
//   The 'userdata' param is the value given in the compiler options, and the 'extuserdata' is the value given in the extension data
typedef size_t (*BCB_Compiler_Extension_GenericCallback)(struct BCB_Compiler*, struct BCB_Compiler_TextStream*, void* userdata, void* extuserdata);
// Called when reading in something named
//   The 'ns' and 'nscrc' params store the namespace text and its CRC32, and the 'name' and 'namecrc' params store the base name text and its CRC
//   Outside of preprocessor callbacks, this may be called multiple times with different namespace values due to the 'USING' command
typedef size_t (*BCB_Compiler_Extension_ReadNamedCallback)(struct BCB_Compiler*, struct BCB_Compiler_TextStream*, void* userdata, void* extuserdata,
                                                           char* ns, uint32_t nscrc, char* name, uint32_t namecrc);

// User-defined extension data
struct BCB_Compiler_Extension {
    void* userdata;                                         // User data passed to callbacks
    BCB_Compiler_Extension_GenericCallback setup;           // Called before parsing the main program. If any additional sources are pushed to the text stream,
                                                            //   they will be parsed before calling 'setup' on the next extension
    BCB_Compiler_Extension_GenericCallback ready;           // Called when done calling 'setup' on all the extensions
    BCB_Compiler_Extension_GenericCallback line;            // Called before reading a line in
    BCB_Compiler_Extension_GenericCallback readpreproccmd;  // Called to read in a preprocessor command
    BCB_Compiler_Extension_GenericCallback readcmd;         // Called to read in a command name
    BCB_Compiler_Extension_ReadNamedCallback preproccmd;    // Called when a preprocessor command name is read in
    BCB_Compiler_Extension_ReadNamedCallback preprocfunc;   // Called when a preprocessor function name and the opening parenthesis are read in
    BCB_Compiler_Extension_ReadNamedCallback preprocvar;    // Called when a preprocessor variable is read in when evaluating an expression
    BCB_Compiler_Extension_ReadNamedCallback cmd;           // Called when a command name is read in
    BCB_Compiler_Extension_ReadNamedCallback func;          // Called when a function name and the opening parenthesis are read in
    BCB_Compiler_Extension_ReadNamedCallback var;           // Called when a variable is read in when evaluating an expression
};

// Returns a NULL-terminated list of the built-in extensions the compiler supports, and optionally outputs the count
char** BCB_Compiler_GetExtensions(size_t* count);

// --- Preprocessor ---

enum BCB_Compiler_PreProc_Var_Type {
    BCB_COMPILER_PREPROC_VAR_STR,
    BCB_COMPILER_PREPROC_VAR_I32,
    BCB_COMPILER_PREPROC_VAR_U32,
    BCB_COMPILER_PREPROC_VAR_I64,
    BCB_COMPILER_PREPROC_VAR_U64
};

// Preproc variable definition
struct BCB_Compiler_PreProc_Var {
    char* name;
    uint32_t namecrc;
    enum BCB_Compiler_PreProc_Var_Type type;
    union {
        char* str;
        int32_t i32;
        uint32_t u32;
        int64_t i64;
        uint64_t u64;
    } data;
};

// Validates names and fills in CRC values
int BCB_Compiler_PreProc_PrepVars(struct BCB_Compiler_PreProc_Var*, size_t count, unsigned flags);
#define BCB_COMPILER_PREPMACRODEFS_SKIPVALIDATION (1U << 0)   // Skip validating names if you already know they are valid

// --- Compiler ---

// Compiled script output
struct BCB_Script;

// Compiler error info output
struct BCB_Compiler_ErrorInfo {
    size_t source;
    char* name;
    void* userdata;
    size_t row;
    size_t col;
};

// Optimization level constants
#define BCB_COMPILER_OPTIONS_OPTIMIZATION_MIN (0)
#define BCB_COMPILER_OPTIONS_OPTIMIZATION_MAX (1)
#define BCB_COMPILER_OPTIONS_OPTIMIZATION_DEBUG (-1)

// Debug info flags and constants
#define BCB_COMPILER_OPTIONS_DEBUG_OFF (0)
#define BCB_COMPILER_OPTIONS_DEBUG_LINENUMBERS (1U << 0)
#define BCB_COMPILER_OPTIONS_DEBUG_CALLSTACK (1U << 1)
#define BCB_COMPILER_OPTIONS_DEBUG_ALL (-1U)

// Compiler options
//   User-defined extensions will override built-in extensions if given the same name.
//   They also need to be listed in 'enable' or 'ondemand' in order to be used.
struct BCB_Compiler_Options {
    void* userdata;
    int optimization;   // Optimization level
    unsigned debug;     // Debug flags
    struct {
        struct {
            struct BCB_Compiler_PreProc_MacroDef* data;
            size_t count;
        } macros;
    } preproc;
    struct {
        struct {
            char** names;
            size_t count;
        } claim;    // Claim these extensions are available (NULL to use 'enable' and 'ondemand')
        struct {
            char** names;
            size_t count;
        } enable;   // Enable these extensions
        struct {
            char** names;
            size_t count;
        } ondemand; // Enable these extensions only if `#require`d
        struct {
            struct BCB_Compiler_Extension* data;
            size_t count;
        } user;     // User-defined extensions
    } extensions;
};

// Compile a program
//   If successful, returns BCB_ERROR_NONE
//   On failure, returns an error code and if 'err' is non-NULL, writes out info about the error
enum BCB_Error BCB_Compile(struct BCB_Compiler_TextStream* in, struct BCB_Compiler_Options*, struct BCB_Script* out, struct BCB_Compiler_ErrorInfo* err);

#ifdef BCBASIC_STATIC

// --- Text streams ---

BCB_PACKEDENUM BCB_Compiler_TextStream_Type {
    BCB_COMPILER_TEXTSTREAM_MEMORY,
    BCB_COMPILER_TEXTSTREAM_CALLBACK,
    #ifndef BCBASIC_NOSTDIO
    BCB_COMPILER_TEXTSTREAM_FILE,
    BCB_COMPILER_TEXTSTREAM_FD
    #endif
};

struct BCB_Compiler_TextStream_Source {
    enum BCB_Compiler_TextStream_Type type;
    char* name;
    void* userdata;
    struct {
        size_t row;
        size_t col;
        char last;
    } backup;
    union {
        struct {
            char* oldbuf;
            size_t oldbufsz;
            size_t oldpos; 
        } mem;
        struct {
            BCB_Compiler_TextStream_DataCallback cb;
        } cb;
        #ifndef BCBASIC_NOSTDIO
        FILE* file;
        int fd;
        #endif
    } src;
};

struct BCB_Compiler_TextStream {
    union {
        char* rw;
        const char* ro;
    } buf;
    size_t pos;
    size_t sz;
    size_t row;
    size_t col;
    struct BCB_VLB(struct BCB_Compiler_TextStream_Source) stack;
    int last;
    unsigned flags;
    struct {
        struct {
            size_t elem;
            size_t row;
            size_t col;
        } start, end;
    } errpos;
};
#define BCB_COMPILER_TEXTSTREAM_UNGET (1U << 0)
#define BCB_COMPILER_TEXTSTREAM_END (1U << 1)

int BCBI_Compiler_TextStream_Update(struct BCB_Compiler_TextStream*);

static inline int BCB_Compiler_TextStream_GetChar_inline(struct BCB_Compiler_TextStream* s) {
    if (!(s->flags & BCB_COMPILER_TEXTSTREAM_END)) {
        if (!(s->flags & BCB_COMPILER_TEXTSTREAM_UNGET)) {
            retry:;
            if (s->pos != s->sz) {
                readchar:;
                unsigned char c = s->buf.rw[s->pos++];
                if (c == '\r' || !c) goto retry;
                if (s->last) {
                    if (s->last != '\n') {
                        if (c != '\n') ++s->col;
                    } else {
                        s->col = 1;
                        ++s->row;
                    }
                }
                s->last = c;
                return c;
            } else if (BCBI_Compiler_TextStream_Update(s)) {
                goto readchar;
            } else {
                return -1;
            }
        } else {
            return s->last;
        }
    } else {
        return -1;
    }
}
static inline void BCB_Compiler_TextStream_SetUnget_inline(struct BCB_Compiler_TextStream* s) {
    s->flags |= BCB_COMPILER_TEXTSTREAM_UNGET;
}

static inline void BCB_Compiler_TextStream_SetErrorStart_inline(struct BCB_Compiler_TextStream* s) {
    s->errpos.start.elem = s->stack.len;
    s->errpos.start.row = s->row;
    s->errpos.start.col = s->col;
}
static inline void BCB_Compiler_TextStream_SetErrorEnd_inline(struct BCB_Compiler_TextStream* s) {
    s->errpos.end.elem = s->stack.len;
    s->errpos.end.row = s->row;
    s->errpos.end.col = s->col;
}
static inline void BCB_Compiler_TextStream_SetErrorPos_inline(struct BCB_Compiler_TextStream* s) {
    s->errpos.start.elem = s->stack.len;
    s->errpos.start.row = s->row;
    s->errpos.start.col = s->col;
    s->errpos.end.elem = s->stack.len;
    s->errpos.end.row = s->row;
    s->errpos.end.col = s->col;
}
static inline void BCB_Compiler_TextStream_SetErrorFirstLine_inline(struct BCB_Compiler_TextStream* s) {
    s->errpos.start.elem = s->stack.len;
    s->errpos.start.row = s->row;
    s->errpos.start.col = 0;
}
static inline void BCB_Compiler_TextStream_SetErrorLastLine_inline(struct BCB_Compiler_TextStream* s) {
    s->errpos.end.elem = s->stack.len;
    s->errpos.end.row = s->row;
    s->errpos.end.col = 0;
}
static inline void BCB_Compiler_TextStream_SetErrorLine_inline(struct BCB_Compiler_TextStream* s) {
    s->errpos.start.elem = s->stack.len;
    s->errpos.start.row = s->row;
    s->errpos.start.col = 0;
    s->errpos.end.elem = s->stack.len;
    s->errpos.end.row = s->row;
    s->errpos.end.col = 0;
}

#endif

#ifdef __cplusplus
}
#endif

#endif
