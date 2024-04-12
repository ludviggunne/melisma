#include <melisma/midi.h>

void write_midi_event(uint32_t dt, struct midi_event e, struct buffer *buf)
{
    char status = ((e.type & 15) << 4) | (e.channel & 15);
    buf_w_vlq(buf, dt);
    buf_putc(buf, status);
    buf_putc(buf, e.data[0]);
    buf_putc(buf, e.data[1]);
}

void write_end_of_track(uint32_t dt, struct buffer *buf)
{
    const unsigned char event[3] = { 0xff, 0x2f, 0x00 };
    buf_w_vlq(buf, dt);
    buf_write(buf, sizeof(event) / sizeof(*event), event);
}
