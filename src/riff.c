#include <melisma/riff.h>
#include <melisma/io.h>

void chunk_write_buf_be(struct chunk ck, struct buffer *buf)
{
    buf_write(buf, 4, ck.fourcc);

    uint32_t size = ck.size;
    if (ck.fcctype) {
        size += 4;
    }
    buf_w_u32_be(buf, size);

    if (ck.fcctype) {
        buf_write(buf, 4, ck.fcctype);
    }
    buf_write(buf, (size_t) ck.size, ck.data);
}

void chunk_write_file_be(struct chunk ck, FILE *f)
{
    fwrite(ck.fourcc, 1, 4, f);

    uint32_t size = ck.size;
    if (ck.fcctype) {
        size += 4;
    }
    fprint_u32_be(f, size);

    if (ck.fcctype) {
        fwrite(ck.fcctype, 1, 4, f);
    }
    fwrite(ck.data, 1, (size_t) ck.size, f);
}

void chunk_write_buf_le(struct chunk ck, struct buffer *buf)
{
    buf_write(buf, 4, ck.fourcc);

    uint32_t size = ck.size;
    if (ck.fcctype) {
        size += 4;
    }
    buf_w_u32_le(buf, size);

    if (ck.fcctype) {
        buf_write(buf, 4, ck.fcctype);
    }
    buf_write(buf, (size_t) ck.size, ck.data);
}

void chunk_write_file_le(struct chunk ck, FILE *f)
{
    fwrite(ck.fourcc, 1, 4, f);

    uint32_t size = ck.size;
    if (ck.fcctype) {
        size += 4;
    }
    fprint_u32_le(f, size);

    if (ck.fcctype) {
        fwrite(ck.fcctype, 1, 4, f);
    }
    fwrite(ck.data, 1, (size_t) ck.size, f);
}

void chunk_from_buf(struct chunk *ck, struct buffer *buf)
{
    ck->data = buf->data;
    ck->size = buf->len;
}
