#ifndef BCBASIC_CRC_H
#define BCBASIC_CRC_H

#include <stdint.h>
#include <stddef.h>

uint32_t BCB_crc32(const void*, size_t);            // Generate a CRC-32 of some bytes
uint32_t BCB_strcrc32(const char*);                 // Generate a CRC-32 of a string
uint32_t BCB_strcasecrc32(const char*);             // Generate a case-insensitive CRC-32 of a string
uint32_t BCB_ccrc32(uint32_t, const void*, size_t); // Continue generating a CRC-32 of some bytes
uint32_t BCB_cstrcrc32(uint32_t, const char*);      // Continue generating a CRC-32 of a string
uint32_t BCB_cstrcasecrc32(uint32_t, const char*);  // Continue generating a case-insensitive CRC-32 of a string

#endif
