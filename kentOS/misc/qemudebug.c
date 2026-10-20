#include <stdint.h>

// Corrected x86 outb function
static inline void outb(uint16_t port, uint8_t val) {
    // AT&T syntax: outb source (val), destination (port)
    __asm__ volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

void qemu_putchar(char c) {
    outb(0xe9, c);
}

void qemu_print(const char *s) {
    while (*s) {
        qemu_putchar(*s++);
    }
} // <-- Closed the function here properly

// Call this from your kernel's main/boot function (e.g., kmain)
void qemuin(void) {
    qemu_print("HIIII\n");
}
