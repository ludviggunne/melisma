#ifndef RIFF_H
#define RIFF_H

#include <stdint.h>
#include <stdio.h>
#include <melisma/buffer.h>

struct chunk {
    const char *fourcc;
    uint32_t size;
    void *data;
};

void chunk_write_buf(struct chunk ck, struct buffer *buf);
void chunk_write_file(struct chunk ck, FILE * f);

#endif                          /* RIFF_H */
