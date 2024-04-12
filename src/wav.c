#include "melisma/buffer.h"
#include "melisma/riff.h"
#include <melisma/wav.h>

struct chunk make_wav_file_chunk(struct buffer *buf, struct wav_spec spec,
                                 size_t data_size, void *data)
{
    struct chunk file, header, content;
    file.fourcc = "RIFF";
    file.fcctype = "WAVE";

    struct buffer subbuf = buf_make();

    /* Header */
    {
        header.fourcc = "fmt ";
        header.fcctype = NULL;
        buf_w_u16_le(&subbuf, spec.format);
        buf_w_u16_le(&subbuf, spec.channels);
        buf_w_u32_le(&subbuf, spec.sample_rate);

        int data_rate =
            (spec.sample_rate * spec.bits_per_sample * spec.channels) / 8;
        buf_w_u32_le(&subbuf, data_rate);

        int block_align = (spec.bits_per_sample * spec.channels) / 8;
        buf_w_u16_le(&subbuf, block_align);

        buf_w_u16_le(&subbuf, spec.bits_per_sample);

        // TODO: extensions
        // ...

        chunk_from_buf(&header, &subbuf);
        chunk_write_buf_le(header, buf);
        buf_reset(&subbuf);
    }

    /* Data */
    {
        content.fourcc = "data";
        content.fcctype = NULL;
        buf_write(&subbuf, data_size, data);
        chunk_from_buf(&content, &subbuf);
        chunk_write_buf_le(content, buf);
    }

    buf_destroy(&subbuf);
    chunk_from_buf(&file, buf);
    return file;
}
