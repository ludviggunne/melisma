const std = @import("std");
const io = std.io;
const heap = std.heap;
const ArrayList = std.ArrayList;
const rand = std.rand;

const midi = @import("midi.zig");

fn makeEvents(list: *ArrayList(midi.MtrkEvent)) !void {
    const dt: u28 = 200;
    const oct: u7 = 6;
    const vel: u7 = 80;
    const seed: u64 = 1;

    var rng = rand.DefaultPrng.init(seed);
    var rn = rng.random();

    var chord_1 = [3]midi.PitchClass{ .c, .e, .g };
    var chord_2: [3]midi.PitchClass = undefined;

    var chord = &chord_1;
    var swap = &chord_2;

    for (0..100) |_| {
        try list.append(.{
            .delta_time = .{ .value = 0 },
            .event = .{
                .midi = midi.Message.noteOn(
                    0,
                    midi.Note.init(chord[0], oct - 1),
                    vel,
                ),
            },
        });
        try list.append(.{
            .delta_time = .{ .value = 0 },
            .event = .{
                .midi = midi.Message.noteOn(
                    0,
                    midi.Note.init(chord[1], oct),
                    vel,
                ),
            },
        });
        try list.append(.{
            .delta_time = .{ .value = 0 },
            .event = .{
                .midi = midi.Message.noteOn(
                    0,
                    midi.Note.init(chord[2], oct + 1),
                    vel,
                ),
            },
        });
        try list.append(.{
            .delta_time = .{ .value = dt },
            .event = .{
                .midi = midi.Message.noteOff(
                    0,
                    midi.Note.init(chord[0], oct - 1),
                    vel,
                ),
            },
        });
        try list.append(.{
            .delta_time = .{ .value = 0 },
            .event = .{
                .midi = midi.Message.noteOff(
                    0,
                    midi.Note.init(chord[1], oct),
                    vel,
                ),
            },
        });
        try list.append(.{
            .delta_time = .{ .value = 0 },
            .event = .{
                .midi = midi.Message.noteOff(
                    0,
                    midi.Note.init(chord[2], oct + 1),
                    vel,
                ),
            },
        });

        const select = rn.intRangeAtMost(usize, 0, 2);
        const third = rn.intRangeAtMost(u7, if (select == 0) 1 else 0, 2);

        const base: u7 = @intFromEnum(chord[select]);
        swap[0] = @enumFromInt(base);
        swap[1] = @enumFromInt(@mod(base + 2 + third, 12));
        swap[2] = @enumFromInt(@mod(base + 7 + @as(u7, if (select == 0) 1 else 0), 12));

        const tmp = chord;
        chord = swap;
        swap = tmp;
    }

    try list.append(.{
        .delta_time = .{ .value = 0 },
        .event = .{ .meta = midi.event.end_of_track },
    });
}

pub fn main() !void {
    var gpa = heap.GeneralPurposeAllocator(.{}){};
    defer _ = gpa.deinit();

    var event_list = ArrayList(midi.MtrkEvent).init(gpa.allocator());
    defer event_list.deinit();

    try makeEvents(&event_list);

    const header = midi.Chunk{ .header = .{} };
    const events = event_list.items;
    const track = midi.Chunk{ .track = .{ .events = events } };

    const stdout = io.getStdOut().writer();

    var buffer = ArrayList(u8).init(gpa.allocator());
    defer buffer.deinit();

    try header.write(stdout, &buffer);
    try track.write(stdout, &buffer);
}
