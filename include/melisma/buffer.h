#ifndef BUFFER_H
#define BUFFER_H

#include <stdlib.h>
#include <stdint.h>

struct buffer {
	char *data;
	size_t len;
	size_t cap;
};

struct buffer buf_make(void);
void buf_destroy(struct buffer *buf);
void buf_putc(struct buffer *buf, char c);
void buf_writes(struct buffer *buf, const char *s);
void buf_write(struct buffer *buf, size_t len, const void *data);
void buf_w_u16_be(struct buffer *buf, uint16_t v);
void buf_w_u32_be(struct buffer *buf, uint32_t v);
void buf_reset(struct buffer *buf);
void buf_w_vlq(struct buffer *buf, uint32_t v);

#endif				/* BUFFER_H */
