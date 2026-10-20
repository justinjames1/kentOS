#define IDT_ENTRIES 256

#include "kernel.h"

struct idt_entry {
    uint16_t offset_low;   // Bits 0..15 of handler address
    uint16_t selector;     // GDT code segment selector (0x08)
    uint8_t zero;          // Unused/Reserved, must be 0
    uint8_t type_attr;     // Access byte/Flags
    uint16_t offset_high;  // Bits 16..31 of handler address
} __attribute__((packed));

struct idt_ptr {
    uint16_t limit;        // Size of table in bytes minus 1
    uint32_t base;         // Linear address of the table array
} __attribute__((packed));

struct idt_entry idt_entry[IDT_ENTRIES];
struct idt_ptr ip;

extern void isr0(void);

void DE(void) {kernel_panic("0x00");}
void UD(void) {kernel_panic("0x06");}
void MC(void) {kernel_panic("0x18");}

void irq0(void){}
void irq1(void){}
void irq2(void){}
void irq3(void){}
void irq4(void){}
void irq5(void){}
void irq6(void){}
void irq7(void){}
void irq8(void){}
void irq9(void){}
void irq10(void){}
void irq11(void){}
void irq12(void){}
void irq13(void){}
void irq14(void){}
void irq15(void){}

void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags) {
    idt_entry[num].offset_low = base & 0xFFFF;
    idt_entry[num].offset_high = (base >> 16) & 0xFFFF;
    idt_entry[num].selector = sel;
    idt_entry[num].zero = 0;
    idt_entry[num].type_attr = flags;
}

void IDT(void) {
    ip.limit = (sizeof(struct idt_entry) * IDT_ENTRIES) - 1;
    ip.base = (uint32_t)idt_entry;

    for (int i = 0; i < IDT_ENTRIES; i++) {
        idt_set_gate(i, 0, 0, 0);
    }

    idt_set_gate(0, (uint32_t)DE, 0x08, 0x8E);
    idt_set_gate(6, (uint32_t)UD, 0x08, 0x8E);
    idt_set_gate(18, (uint32_t)MC, 0x08, 0x8E);



     idt_set_gate(0x20, (uint32_t)irq0, 0x08, 0x8E);
     idt_set_gate(0x21, (uint32_t)irq1, 0x08, 0x8E);
     idt_set_gate(0x22, (uint32_t)irq2, 0x08, 0x8E);
     idt_set_gate(0x23, (uint32_t)irq3, 0x08, 0x8E);
     idt_set_gate(0x24, (uint32_t)irq4, 0x08, 0x8E);
     idt_set_gate(0x25, (uint32_t)irq5, 0x08, 0x8E);
     idt_set_gate(0x26, (uint32_t)irq6, 0x08, 0x8E);
     idt_set_gate(0x27, (uint32_t)irq7, 0x08, 0x8E);
     idt_set_gate(0x28, (uint32_t)irq8, 0x08, 0x8E);
     idt_set_gate(0x29, (uint32_t)irq9, 0x08, 0x8E);
     idt_set_gate(0x2A, (uint32_t)irq10, 0x08, 0x8E);
     idt_set_gate(0x2B, (uint32_t)irq11, 0x08, 0x8E);
     idt_set_gate(0x2C, (uint32_t)irq12, 0x08, 0x8E);
     idt_set_gate(0x2D, (uint32_t)irq13, 0x08, 0x8E);
     idt_set_gate(0x2E, (uint32_t)irq15, 0x08, 0x8E);
     idt_set_gate(0x2F, (uint32_t)irq15, 0x08, 0x8E);


    __asm__ volatile("lidt %0" : : "m"(ip));
}
