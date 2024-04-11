//!
//! MIDI Message.
//!

const Message = @This();

kind: Kind,
channel: u4,
data: [2]u8,

pub const PitchClass = enum(u7) { c, db, d, eb, e, f, gb, g, ab, a, bb, b };

pub const Note = struct {
    cls: PitchClass,
    oct: u7,

    pub fn init(cls: PitchClass, oct: u7) Note {
        return .{ .cls = cls, .oct = oct };
    }

    pub fn data(self: Note) u8 {
        const cls_as_u8: u8 = @intFromEnum(self.cls);
        const oct_as_u8: u8 = @intCast(self.oct);
        return oct_as_u8 * 12 + cls_as_u8;
    }
};

pub fn noteOn(channel: u4, note: Note, velocity: u7) Message {
    return .{
        .kind = .note_on,
        .channel = channel,
        .data = [2]u8{ note.data(), @intCast(velocity) },
    };
}

pub fn noteOff(channel: u4, note: Note, velocity: u7) Message {
    return .{
        .kind = .note_off,
        .channel = channel,
        .data = [2]u8{ note.data(), @intCast(velocity) },
    };
}

// TODO: more constructors

pub fn write(self: Message, writer: anytype) !void {
    const kind_bits: u8 = @intFromEnum(self.kind);
    const channel_bits: u8 = @intCast(self.channel);
    const status: u8 = (kind_bits << 4) | channel_bits;
    try writer.writeByte(status);
    try writer.writeAll(&self.data);
}

pub const Kind = enum(u4) {
    note_off = 0b1000,
    note_on = 0b1001,
    // TODO: more event types
};
