#include <types.h>
#include <tty.h>
#include <kstdio.h>
#include <gdt.h>

__attribute__((noreturn)) void kmain(void *multiboot_structure, uint32_t magicnumber)
{
    tty_init();
    kprintf("--------------------This is a test of the operating system--------------------\n");
    kprintf("Loading GDT...\n");
    __gdt_init();
    kprintf("GDT Loaded Successfully...\n");
    while (1)
        ;
}