#!/usr/bin/env bash
set -e # Exit on any error

# === CONFIG ===
CC=gcc
CFLAGS="-Wall -Wextra -std=c23"
SRC_DIR="src"
BUILD_DIR="build"
OUT="$BUILD_DIR/main"

# Include directories
INCLUDES="-Iinclude"

# Libraries to Link
LIBS="-lcurl"

# === BUILD ===
mkdir -p "$BUILD_DIR"

# echo "🔧 Compiling C sources from $SRC_DIR ..."
# Find all .c files recursively and compile them
$CC $CFLAGS $INCLUDES $(find "$SRC_DIR" -name "*.c") -o "$OUT" $LIBS

# echo "✅ Build complete: $OUT"

# run the binary
./build/main
