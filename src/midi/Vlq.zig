//!
//! Variable Length Quantity readin & writing.
//! The maximum bitsize of a VLQ in MIDI streams is 28.
//!

const Vlq = @This();

value: u28,

pub fn write(self: Vlq, writer: anytype) !void {
    var byte_size: usize = 1;
    var buf: [4]u8 = undefined;
    var value = self.value;

    buf[3] = @truncate(value & 0x7f);
    value >>= 7;

    while (value > 0) : (byte_size += 1) {
        const byte: u8 = @truncate((value & 0x7f) | 0x80);
        value >>= 7;
        buf[3 - byte_size] = byte;
    }

    try writer.writeAll(buf[4 - byte_size ..]);
}

test write {
    // TODO: more cases
    const vlq: Vlq = .{ .value = 2097151 };
    const expected: [4]u8 = .{ 0xff, 0xff, 0x7f, 0x0 };
    var actual: [4]u8 = .{0} ** 4;

    const std = @import("std");
    var stream = std.io.fixedBufferStream(&actual);
    try vlq.write(stream.writer());
    try std.testing.expectEqualSlices(u8, &expected, &actual);
}
