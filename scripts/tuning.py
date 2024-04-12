#!/usr/bin/env python3

import sys

path = sys.argv[1]

this_file = '/'.join(__file__.split('/')[-2:])

tuning = [1.0, 2.0, 3.0]

with open(path, 'w') as f:
    f.write(f"/* Generated with {this_file} */\n")
    f.write(f"\n")
    f.write(f"#ifndef TUNING_H\n")
    f.write(f"#define TUNING_H\n")
    f.write(f"\n")
    f.write("static const float tuning[] = {\n")
    for value in tuning:
        f.write(f"    {value}f,\n")
    f.write("};\n")
    f.write(f"\n")
    f.write("#endif /* TUNING_H */\n")

