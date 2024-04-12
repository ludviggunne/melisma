#include "melisma/buffer.h"
#include <stdio.h>
#include <melisma/midi.h>
#include <melisma/riff.h>
#include <melisma/io.h>

#define END -1
#define C(x)  12 * x
#define Cs(x) 12 * x + 1
#define Db(x) 12 * x + 1
#define D(x)  12 * x + 2
#define Ds(x) 12 * x + 3
#define Eb(x) 12 * x + 3
#define E(x)  12 * x + 4
#define F(x)  12 * x + 5
#define Fs(x) 12 * x + 6
#define Gb(x) 12 * x + 6
#define G(x)  12 * x + 7
#define Gs(x) 12 * x + 8
#define Ab(x) 12 * x + 8
#define A(x)  12 * x + 9
#define As(x) 12 * x + 10
#define Bb(x) 12 * x + 10
#define B(x)  12 * x + 11

int song[] = {
    2, C(5), G(5), C(6), D(6), E(6), END,
    2, D(5), A(5), D(6), E(6), F(6), END,
    2, G(4), G(5), D(6), E(6), F(6), END,
    1, C(5), G(5), C(6), D(6), E(6), END,
    1, B(4), G(5), C(6), D(6), E(6), END,
    1, A(4), E(5), A(5), B(5), C(6), E(5), C(6), D(6), E(6), END,
    1, G(4), E(5), A(5), B(5), C(6), E(5), C(6), D(6), E(6), END,
    2, F(4), D(5), A(5), C(6), D(6), END,
    1, F(4), D(5), Ab(5), C(6), D(6), END,
    1, D(4), F(5), Ab(5), C(6), D(6), END,
    1, E(4), G(4), C(5), G(5), B(5), C(6), G(6), E(6), D(6), END,
    1, Eb(4), G(4), C(5), G(5), A(5), C(6), G(6), Eb(6), D(6), END,
    1, D(4), A(4), D(5), A(5), Cs(5), D(6), A(6), F(6), E(6), END,
    1, Cs(4), A(4), E(5), A(5), C(5), Cs(6), A(6), E(6), Ds(6), END,
    1, C(4), A(4), F(5), A(5), B(5), C(6), A(6), F(6), E(6), END,
    1, Ab(3), Fs(4), C(5), E(5), Fs(5), B(5), C(6), D(6), Eb(6), END,
    1, G(3), G(4), G(5), C(6), D(6), G(6), F(6), C(7), D(7), END,
    1, G(3), G(4), G(5), B(5), D(6), G(6), F(6), B(6), D(7), END,
    2, C(3), C(4), C(6), C(7), G(6), C(6), B(5), E(6), E(5), END,
    2, C(3), E(4), C(6), C(7), G(6), END,
    2, C(3), C(4), G(4), E(5), C(6), END,
};

int note_len = 48;
int velocity = 127;

void play_note(struct buffer *buf, int key)
{
    struct midi_event e;
    e.data[0] = key;
    e.data[1] = velocity;
    e.channel = 0;
    e.type = MIDI_EVENT_TYPE_NOTE_ON;
    write_midi_event(0, e, buf);
    e.type = MIDI_EVENT_TYPE_NOTE_OFF;
    write_midi_event(note_len, e, buf);
}

int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv;

    struct buffer buf = buf_make();

    /* HEADER */
    struct chunk hdr;
    hdr.fourcc = MIDI_HDR_CHUNK_TYPE;
    buf_w_u16_be(&buf, MIDI_FORMAT_SINGLE);
    buf_w_u16_be(&buf, 1);
    buf_w_u16_be(&buf, 256);
    hdr.size = buf.len;
    hdr.data = buf.data;
    chunk_write_file(hdr, stdout);
    buf_reset(&buf);

    /* TRACK */
    size_t song_size = sizeof(song) / sizeof(*song);
    size_t begin = 0, end;

    while (begin < song_size) {
        int repeat = (int) song[begin];
        begin++;
        end = begin;

        while (song[end] != END && end < song_size) {
            end++;
        }

        while (repeat--) {
            struct midi_event e;
            e.type = MIDI_EVENT_TYPE_NOTE_ON;
            e.channel = 0;
            e.data[0] = song[begin] - 12;
            e.data[1] = velocity;
            write_midi_event(0, e, &buf);

            for (size_t i = begin; i < end; i++) {
                play_note(&buf, song[i]);
            }

            for (size_t i = end - 2; i > begin; i--) {
                play_note(&buf, song[i]);
            }

            e.type = MIDI_EVENT_TYPE_NOTE_OFF;
            write_midi_event(0, e, &buf);
        }

        begin = end + 1;
    }

    struct midi_event e;
    e.type = MIDI_EVENT_TYPE_NOTE_ON;
    e.channel = 0;
    e.data[0] = C(3);
    e.data[1] = velocity;
    write_midi_event(0, e, &buf);
    e.type = MIDI_EVENT_TYPE_NOTE_OFF;
    write_midi_event(256, e, &buf);

    write_end_of_track(512, &buf);
    struct chunk trk;
    trk.fourcc = MIDI_TRK_CHUNK_TYPE;
    trk.size = buf.len;
    trk.data = buf.data;

    chunk_write_file(trk, stdout);

    buf_destroy(&buf);
}
