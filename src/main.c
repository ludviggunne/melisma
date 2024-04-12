#include "melisma/buffer.h"
#include <stdio.h>
#include <melisma/midi.h>
#include <melisma/riff.h>
#include <melisma/io.h>

const unsigned char mel[] = { 60, 61, 63, 64, 66, 67, 69, 70, 72 };

int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv;

    struct buffer buf = buf_make();

    struct chunk hdr;
    hdr.fourcc = MIDI_HDR_CHUNK_TYPE;

    /* Single track */
    buf_w_u16_be(&buf, MIDI_FORMAT_SINGLE);
    buf_w_u16_be(&buf, 1);
    /* Division = 256 */
    buf_w_u16_be(&buf, 256);

    hdr.size = buf.len;
    hdr.data = buf.data;

    /* Write chunk */
    chunk_write_file(hdr, stdout);
    buf_reset(&buf);

    struct chunk trk;
    trk.fourcc = MIDI_TRK_CHUNK_TYPE;

    const unsigned len = 32;

    struct midi_event evt;
    evt.channel = 0;
    evt.data[1] = 100;

    const size_t mel_len = sizeof(mel) / sizeof(*mel);
    for (int k = 0; k < 4; k++) {
        for (size_t i = 0; i < mel_len; i++) {
            evt.type = MIDI_EVENT_TYPE_NOTE_ON;
            evt.data[0] = mel[i] + 12;
            write_midi_event(0, evt, &buf);
            evt.type = MIDI_EVENT_TYPE_NOTE_OFF;
            write_midi_event(len, evt, &buf);
        }

        for (size_t i = 1; i < mel_len; i++) {
            evt.type = MIDI_EVENT_TYPE_NOTE_ON;
            evt.data[0] = mel[mel_len - 1 - i] + 12;
            write_midi_event(0, evt, &buf);
            evt.type = MIDI_EVENT_TYPE_NOTE_OFF;
            write_midi_event(len, evt, &buf);
        }
    }
    write_end_of_track(256, &buf);

    trk.size = buf.len;
    fprintf(stderr, "%x\n", trk.size);
    trk.data = buf.data;

    /* Write chunk */
    chunk_write_file(trk, stdout);

    buf_destroy(&buf);
}
