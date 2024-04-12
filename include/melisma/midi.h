#ifndef MIDI_H
#define MIDI_H

#include <melisma/buffer.h>

#define MIDI_HDR_CHUNK_TYPE      "MThd"
#define MIDI_TRK_CHUNK_TYPE      "MTrk"
#define MIDI_FORMAT_SINGLE       0
#define MIDI_FORMAT_SIMULTANEUS  1
#define MIDI_FORMAT_INDEPENDENT  2
#define MIDI_EVENT_TYPE_NOTE_ON  8
#define MIDI_EVENT_TYPE_NOTE_OFF 9

struct hdr_data {
    uint16_t format;
    uint16_t ntrks;
    uint16_t division;
};

struct midi_event {
    int type;
    int channel;
    int data[2];
};

void write_midi_event(uint32_t dt, struct midi_event e, struct buffer *buf);
void write_end_of_track(uint32_t dt, struct buffer *buf);

#endif                          /* MIDI_H */
