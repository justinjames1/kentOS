.set ALIGN,    1<<0             /* align loaded modules on page boundaries */
.set MEMINFO,  1<<1             /* provide memory map */
.set FLAGS,    ALIGN | MEMINFO  /* this is the Multiboot 'flag' field */
.set MAGIC,    0x1BADB002       /* 'magic number' lets bootloader find the header */
.set CHECKSUM, -(MAGIC + FLAGS) /* checksum of above, to prove we are multiboot */

.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

.section .text
.global _start
.extern DE
.type _start, @function

_start:
	mov $stack_top, %esp

	# Load our clean GDT so selector 0x08 is explicitly defined
	lgdt (gdt_descriptor)
	
	# Perform a long jump to reload the CS (Code Segment) register with 0x08
	ljmp $0x08, $.reload_segments

.reload_segments:
	# Reload data segment registers with our 0x10 data selector
	mov $0x10, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs
	mov %ax, %ss

	# Call  main kernel execution
	call kernel_main

	cli
1:	hlt
	jmp 1b

.size _start, . - _start

.macro no_error_code_handler vector
.global isr\vector
isr\vector:
    pusha           # Save all general-purpose registers
    call DE         # Jump to C panic handler inside panic.c
    popa            # Restore registers if it ever returns
    iret            # Hardware instruction required to clear the interrupt stack
.endm

# Auto-generate the actual handler for vector 0 (Divide Error)
no_error_code_handler 0
.align 4
gdt_start:
    .long 0x0
    .long 0x0

    .word 0xFFFF
    .word 0x0000
    .byte 0x00
    .byte 0x9A
    .byte 0xCF
    .byte 0x00

    .word 0xFFFF
    .word 0x0000
    .byte 0x00
    .byte 0x92
    .byte 0xCF
    .byte 0x00
gdt_end:

gdt_descriptor:
    .word (gdt_end - gdt_start) - 1 # GDT Size limit
    .long gdt_start                 # Linear address of the table start
