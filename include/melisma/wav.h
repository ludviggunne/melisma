#ifndef WAV_H
#define WAV_H

#include <melisma/riff.h>
#include <melisma/buffer.h>

#define WAVE_FORMAT_PCM        0x0001
#define WAVE_FORMAT_IEEE_FLOAT 0x0003
#define WAVE_FORMAT_ALAW       0x0006
#define WAVE_FORMAT_MULAW      0x0007
#define WAVE_FORMAT_EXTENSIBLE 0xfffe

struct wav_spec {
    int format;
    int channels;
    int sample_rate;
    int bits_per_sample;
};

struct chunk make_wav_file_chunk(struct buffer *buf, struct wav_spec spec,
                                 size_t data_size, void *data);

#endif                          /* WAV_H */
