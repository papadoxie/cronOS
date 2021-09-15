OUTPUT_FORMAT(elf32-i386)
OUTPUT_ARCH(i386:i386)
ENTRY(_start)

SECTIONS
{
    . = 0x00100000;

    .text :{
        *(.multiboot)
        *(.text)
    }

    .data :{
        start_ctors = .;
        *(.ctor*)
        end_ctors = .;
        start_dtors = .;
        *(.dtor*)
        end_dtors = .;
        *(.data)
    }

    .rodata :{
        *(.rodata)
    }

    .bss :{
        sbss = .;
        *(COMMON)
        *(.bss)
        ebss = .;
    }

    /DISCARD/ :{
        *(.fini_array*)
        *(.comment)
    }
}