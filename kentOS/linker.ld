ENTRY(_start)

SECTIONS
{
    /* Multiboot requires the header to be within the first 8 KiB */
    . = 1M;

    .text : ALIGN(4K)
    {
        /* FORCE the multiboot section to the absolute top of the file */
        *(.multiboot)
        *(.text)
    }

    .rodata : ALIGN(4K)
    {
        *(.rodata)
    }

    .data : ALIGN(4K)
    {
        *(.data)
    }

    .bss : ALIGN(4K)
    {
        *(COMMON)
        *(.bss)
    }
}
