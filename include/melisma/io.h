#ifndef IO_H
#define IO_H

#include <stdio.h>
#include <stdint.h>

void fprint_u16_be(FILE * f, uint16_t v);
void fprint_u32_be(FILE * f, uint32_t v);

#endif                          /* IO_H */
