#ifndef STREAM_PARSER_H
#define STREAM_PARSER_H

#include <stdint.h>

uint32_t stream_read_u32_be(void **data);
uint16_t stream_read_u16_be(void **data);
uint32_t stream_read_u32_le(void **data);
uint16_t stream_read_u16_le(void **data);
char *stream_read_id(void **data);

#endif
