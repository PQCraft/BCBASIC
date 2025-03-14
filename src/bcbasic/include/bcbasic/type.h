#ifndef BCBASIC_TYPE_H
#define BCBASIC_TYPE_H

#include "attribs.h"

#include <stddef.h>

BCB_PACKEDENUM BCB_TypeGroup {    // Type groups
    BCB_TYPEGROUP_NONE,     // Used for NULL, VOID, and skipped arguments
    BCB_TYPEGROUP_REGULAR,  // Regular data (single-type single-offset data)
    BCB_TYPEGROUP_STRUCT,   // Struct (multi-type multi-offset data)
    BCB_TYPEGROUP_UNION,    // Union (multi-type single-offset data)
    BCB_TYPEGROUP_VARREF,   // Variable reference
    BCB_TYPEGROUP_CMDREF,   // Command reference
};

BCB_PACKEDENUM BCB_TypeID {   // Type IDs
    BCB_TYPEID_STRING,  // String
    BCB_TYPEID_I8,      // 8-bit integer
    BCB_TYPEID_U8,      // 8-bit unsigned integer
    BCB_TYPEID_I16,     // 16-bit integer
    BCB_TYPEID_U16,     // 16-bit unsigned integer
    BCB_TYPEID_I32,     // 32-bit integer
    BCB_TYPEID_U32,     // 32-bit unsigned integer
    BCB_TYPEID_I64,     // 64-bit integer
    BCB_TYPEID_U64,     // 64-bit unsigned integer
    BCB_TYPEID_F32,     // Float
    BCB_TYPEID_F64,     // Double
};

struct BCB_Type {   // Type info struct
    enum BCB_TypeGroup group;   // Type group
    union {
        enum BCB_TypeID id; // Type ID for BCB_TYPEGROUP_REGULAR
        size_t index;  // Struct/union definition for BCB_TYPEGROUP_{STRUCT|UNION}
    };
    size_t dim;        // Array dimensions (0 if not an array)
    size_t* sizes;    // Sizes of each dimension
};

struct BCB_StructElem {
    size_t offset;
    struct bcb_type type;
    char* name;
};

struct BCB_StructDef {
    struct BCB_StructElem* elems;
    size_t elemct;
    size_t size;
};

struct BCB_UnionElem {
    struct BCB_Type type;
    char* name;
};

struct BCB_UnionDef {
    struct BCB_UnionElem* elems;
    size_t elemct;
    size_t size;
};

#endif
