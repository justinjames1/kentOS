set -e

echo "=== Starting KentOS Build ==="

echo "Assembling boot.asm..."
as --32 boot.asm -o boot.o

echo "Compiling kernel.c..."
gcc -m32 -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

echo "Linking kernel binary..."
ld -m elf_i386 -T linker.ld -o Kentos boot.o kernel.o

echo "Cleaning up temporary build artifacts (.o files)..."
rm boot.o kernel.o

echo  "Build Successful! Launching QEMU..."

# 5. Boot the OS in the emulator
qemu-system-i386 -kernel Kentos
