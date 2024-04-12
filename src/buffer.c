#include <melisma/buffer.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define BUFFER_INIT_CAPACITY 16

struct buffer buf_make(void)
{
    struct buffer buf;
    buf.cap = BUFFER_INIT_CAPACITY;
    buf.len = 0;
    buf.data = malloc(sizeof(*buf.data) * buf.cap);
    return buf;
}

void buf_destroy(struct buffer *buf)
{
    free(buf->data);
    buf->len = 0;
    buf->cap = 0;
}

void buf_putc(struct buffer *buf, char c)
{
    if (buf->len == buf->cap) {
        size_t new_cap = buf->cap * 2;
        char *new_data = malloc(sizeof(*new_data) * new_cap);
        memcpy(new_data, buf->data, buf->len);
        free(buf->data);
        buf->data = new_data;
        buf->cap = new_cap;
    }
    buf->data[buf->len++] = c;
}

void buf_writes(struct buffer *buf, const char *s)
{
    size_t len = strlen(s);
    buf_write(buf, len, s);
}

void buf_write(struct buffer *buf, size_t len, const void *data)
{
    if (buf->len + len > buf->cap) {
        size_t new_cap = buf->cap * 2;
        while (buf->len + len > new_cap) {
            new_cap *= 2;
        }
        char *new_data = malloc(sizeof(*new_data) * new_cap);
        memcpy(new_data, buf->data, buf->len);
        free(buf->data);
        buf->data = new_data;
        buf->cap = new_cap;
    }
    memcpy(&buf->data[buf->len], data, len);
    buf->len += len;
}

void buf_w_u16_be(struct buffer *buf, uint16_t v)
{
    buf_putc(buf, (v >> 8) & 255);
    buf_putc(buf, v & 255);
}

void buf_w_u32_be(struct buffer *buf, uint32_t v)
{
    buf_putc(buf, (v >> 24) & 255);
    buf_putc(buf, (v >> 16) & 255);
    buf_putc(buf, (v >> 8) & 255);
    buf_putc(buf, v & 255);
}

void buf_w_u16_le(struct buffer *buf, uint16_t v)
{
    buf_putc(buf, v & 255);
    buf_putc(buf, (v >> 8) & 255);
}

void buf_w_u32_le(struct buffer *buf, uint32_t v)
{
    buf_putc(buf, v & 255);
    buf_putc(buf, (v >> 8) & 255);
    buf_putc(buf, (v >> 16) & 255);
    buf_putc(buf, (v >> 24) & 255);
}

void buf_reset(struct buffer *buf)
{
    buf->len = 0;
}

void buf_w_vlq(struct buffer *buf, uint32_t v)
{
    unsigned char tmp[4];
    size_t size = 1;

    tmp[3] = v & 127;
    v >>= 7;

    while (v) {
        tmp[3 - size] = (v & 127) | 128;
        v >>= 7;
        size++;
    }

    buf_write(buf, size, &tmp[4 - size]);
}
