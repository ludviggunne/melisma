const std = @import("std");

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const exe = b.addExecutable(.{
        .name = "melisma",
        .root_source_file = .{ .path = "src/main.zig" },
        .target = target,
        .optimize = optimize,
    });

    const midi = b.addModule("midi", .{
        .root_source_file = .{ .path = "src/midi/root.zig" },
    });

    exe.root_module.addImport("midi", midi);

    b.installArtifact(exe);
}
