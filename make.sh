#!/bin/bash
set -e

BUILD=/home/tobias/code/carbon/build/
SRC=/home/tobias/code/carbon/src/


for f in "$SRC"/*.c; do
    [ -f "$f" ] || continue    # skip if no .c files
    obj="$BUILD/$(basename "${f%.c}.o")"
    gcc -c "$f" -o "$obj"
done

mkdir -p "$BUILD"/carbon
gcc -o "$BUILD/carbon/carbon" "$BUILD"/*.o
