#include <melisma/riff.h>
#include <melisma/io.h>

void chunk_write_buf(struct chunk ck, struct buffer *buf)
{
    buf_write(buf, 4, ck.fourcc);
    buf_w_u32_be(buf, ck.size);
    buf_write(buf, (size_t) ck.size, ck.data);
}

void chunk_write_file(struct chunk ck, FILE *f)
{
    fwrite(ck.fourcc, 1, 4, f);
    fprint_u32_be(f, ck.size);
    fwrite(ck.data, 1, (size_t) ck.size, f);
}
