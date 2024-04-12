#ifndef RIFF_H
#define RIFF_H

#include <stdint.h>
#include <stdio.h>
#include <melisma/buffer.h>

struct chunk {
    const char *fourcc;
    uint32_t size;
    const char *fcctype;
    void *data;
};

void chunk_from_buf(struct chunk *ck, struct buffer *buf);

void chunk_write_buf_be(struct chunk ck, struct buffer *buf);
void chunk_write_file_be(struct chunk ck, FILE * f);
void chunk_write_buf_le(struct chunk ck, struct buffer *buf);
void chunk_write_file_le(struct chunk ck, FILE * f);

struct chunk chunk_read_be(void *data);
struct chunk chunk_read_file_be(FILE * f);
struct chunk chunk_read_le(void *data);
struct chunk chunk_read_file_le(FILE * f);

#endif                          /* RIFF_H */
