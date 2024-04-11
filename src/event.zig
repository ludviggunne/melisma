//!
//! MIDI events.
//!

const Vlq = @import("Vlq.zig");
const Message = @import("Message.zig");

pub const MtrkEvent = struct {
    delta_time: Vlq,
    event: Event,
};

pub const end_of_track: []const u8 = &.{ 0xff, 0x2f, 0x00 };

pub const Event = union(Event.Kind) {
    midi: Message,
    sysex: struct {},
    meta: []const u8,

    pub const Kind = enum {
        midi,
        sysex,
        meta,
    };
};
