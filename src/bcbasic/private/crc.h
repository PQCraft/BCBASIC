#ifndef BCBASIC_CRC_H
#define BCBASIC_CRC_H

#include <stdint.h>
#include <stddef.h>

uint32_t bcb_crc32(const void*, size_t);
uint32_t bcb_strcrc32(const char*);
uint32_t bcb_strcasecrc32(const char*);
uint32_t bcb_ccrc32(uint32_t, const void*, size_t);
uint32_t bcb_cstrcrc32(uint32_t, const char*);
uint32_t bcb_cstrcasecrc32(uint32_t, const char*);

#endif
