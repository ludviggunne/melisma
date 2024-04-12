#include <stdio.h>
#include <math.h>
#include <melisma/wav.h>
#include <melisma/tuning.h>

#define SAMPLE_RATE 44100
#define FREQUENCY 440

int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv;

    struct buffer ckbuf = buf_make();
    struct buffer databuf = buf_make();

    struct wav_spec spec;
    spec.format = WAVE_FORMAT_PCM;
    spec.channels = 1;
    spec.sample_rate = SAMPLE_RATE;
    spec.bits_per_sample = 16;

    /* A */
    for (int i = 0; i < SAMPLE_RATE; i++) {
        float t = (float) i / (float) SAMPLE_RATE;
        float amp = sinf(t * FREQUENCY * M_PI * 2);
        amp *= (float) (1 << 15);
        int16_t sample = (int16_t) amp;
        buf_w_u16_le(&databuf, *(uint16_t *) & sample);
    }

    /* E */
    for (int i = 0; i < SAMPLE_RATE; i++) {
        float t = (float) i / (float) SAMPLE_RATE;
        float amp = sinf(t * FREQUENCY * M_PI * 3);
        amp *= (float) (1 << 15);
        int16_t sample = (int16_t) amp;
        buf_w_u16_le(&databuf, *(uint16_t *) & sample);
    }

    struct chunk file =
        make_wav_file_chunk(&ckbuf, spec, databuf.len, databuf.data);

    chunk_write_file_le(file, stdout);
}
