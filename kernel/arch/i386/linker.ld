ENTRY(start)

KERNEL_VIRTUAL_BASE = 0xc0000000;
KERNEL_PHYSICAL_BASE = 0x00100000;

SECTIONS
{
    . = KERNEL_VIRTUAL_BASE + KERNEL_PHYSICAL_BASE;

    kernel_image_start = .;

    .text ALIGN(4K) : AT (ADDR(.text) - KERNEL_VIRTUAL_BASE)
    {
        *(.multiboot)
        *(.text*)
    }

    .rodata ALIGN(4K) : AT (ADDR(.rodata) - KERNEL_VIRTUAL_BASE)
    {
        *(.rodata*)
    }

    .data ALIGN(4K) : AT (ADDR(.data) - KERNEL_VIRTUAL_BASE)
    {
        *(.data*)
    }

    .bss ALIGN(4K) : AT (ADDR(.bss) - KERNEL_VIRTUAL_BASE)
    {
        *(COMMON)
        *(.bss*)
    }

    kernel_image_end = .;
}
