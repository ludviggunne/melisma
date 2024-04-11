//!
//! MIDI Message.
//!

const Message = @This();

type_: Type,
channel: u4,
data: [2]u8,

pub fn noteOn(channel: u4, key: u7, velocity: u7) Message {
    return .{
        .type_ = .note_on,
        .channel = channel,
        .data = [2]u8{ @intCast(key), @intCast(velocity) },
    };
}

pub fn noteOff(channel: u4, key: u7, velocity: u7) Message {
    return .{
        .type_ = .note_off,
        .channel = channel,
        .data = [2]u8{ @intCast(key), @intCast(velocity) },
    };
}

// TODO: more constructors

pub fn write(self: Message, writer: anytype) !void {
    const type_bits: u8 = @intFromEnum(self.type_);
    const channel_bits: u8 = @intCast(self.channel);
    const status: u8 = (type_bits << 4) | channel_bits;
    try writer.writeByte(status);
    try writer.writeAll(&self.data);
}

pub const Type = enum(u4) {
    note_off = 8,
    note_on = 9,
    // TODO: more event types
};
