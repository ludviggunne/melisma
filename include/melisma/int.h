#ifndef INT_H
#define INT_H

#include <stdint.h>

uint32_t read_u32_be(void *ptr);
uint16_t read_u16_be(void *ptr);
uint32_t read_u32_le(void *ptr);
uint16_t read_u16_le(void *ptr);

#endif                          /* INT_H */
