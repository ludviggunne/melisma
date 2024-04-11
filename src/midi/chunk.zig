//!
//! MIDI file chunk.
//!

const std = @import("std");
const ArrayList = std.ArrayList;
const Vlq = @import("Vlq.zig");
const event = @import("event.zig");
const MtrkEvent = event.MtrkEvent;
const Message = @import("Message.zig");

/// MIDI file chunk.
pub const Chunk = union(enum) {
    header: struct {
        format: enum(u16) {
            single = 0,
            simultaneous = 1,
            independent = 2,
        } = .single,
        ntrks: u16 = 1,
        // TODO: SMPTE utility
        division: u16 = 96,
    },
    track: struct {
        events: []const MtrkEvent,
    },

    fn typeText(self: @This()) []const u8 {
        return switch (self) {
            .header => "MThd",
            .track => "MTrk",
        };
    }

    pub fn write(self: Chunk, writer: anytype, buffer: *ArrayList(u8)) !void {
        buffer.clearRetainingCapacity();
        try writer.writeAll(self.typeText());
        try writeValue(self, buffer.writer());
        try writer.writeInt(u32, @intCast(buffer.items.len), .big);
        try writer.writeAll(buffer.items);
    }
};

/// Writes a Zig value in the format specified by MIDI
fn writeValue(v: anytype, writer: anytype) !void {
    const T = @TypeOf(v);
    const info = @typeInfo(T);

    // Special cases
    switch (T) {
        Vlq,
        Message,
        => {
            try v.write(writer);
            return;
        },
        else => {},
    }

    switch (info) {
        .Struct => |s| inline for (s.fields) |f| {
            try writeValue(@field(v, f.name), writer);
        },
        .Int => {
            try writer.writeInt(T, v, .big);
        },
        .Union => |u| {
            if (u.tag_type == null) {
                @compileError("Union type " ++ @typeName(T) ++ " has no tag");
            }
            inline for (u.fields) |u_field| {
                if (v == @field(u.tag_type.?, u_field.name)) {
                    try writeValue(@field(v, u_field.name), writer);
                    return;
                }
            }
            unreachable;
        },
        .Enum => |e| {
            const Backing = e.tag_type;
            try writer.writeInt(Backing, @intFromEnum(v), .big);
        },
        .Pointer => |p| {
            switch (p.size) {
                .Slice => {
                    for (v) |e| {
                        try writeValue(e, writer);
                    }
                },
                else => @compileError("Unsupported type for writing: " ++ @typeName(T)),
            }
        },
        .Array => {
            for (v) |e| {
                try writeValue(e, writer);
            }
        },
        else => @compileError("Unsupported type for writing: " ++ @typeName(T)),
    }
}
