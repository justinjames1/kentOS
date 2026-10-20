#!/bin/bash
set -e

cd "$(dirname "$0")"

echo "=== Starting KentOS Build ==="

CFLAGS=(
    -v
    -m32
    -std=gnu99
    -ffreestanding
    -fno-pie
    -fno-pic
    -fno-stack-protector
    -O2
    -Wall
    -Wextra
    -I.
)

# Enable globstar for recursive folder matching
shopt -s globstar

echo "Cleaning old object files..."
rm -f boot.o kentos.bin **/*.o 2>/dev/null || true

echo "Assembling boot.asm..."
as --32 boot.asm -o boot.o

echo "Launching sequential compilation waterfall..."
for file in **/*.c; do
    echo "--- Compiling: $file ---"
    # PIPESTATUS ensures the script exits instantly if a C file fails to compile
    gcc "${CFLAGS[@]}" -c "$file" -o "${file%.c}.o" 2>&1 | pv -qL 10000
done

echo "Linking KentOS..."
# Safely collects boot.o and all nested object files across all 7 directories
OBJECT_FILES=$(find . -name "*.o" ! -name "boot.o")
ld -m elf_i386 -T linker.ld -o kentos.bin boot.o $OBJECT_FILES

echo "=== KentOS Build Complete ==="

echo "=== Launching in QEMU ==="
# Launches your kernel directly. 
# -debugcon stdio redirects port 0xe9 output right back to this terminal window.
qemu-system-i386 -kernel kentos.bin -debugcon stdio
