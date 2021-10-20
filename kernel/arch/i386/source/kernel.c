#include <types.h>
#include <kstdio.h>
#include <gdt.h>

__attribute__((noreturn)) void kmain(void *multiboot_structure, uint32_t magicnumber)
{
    kprintf("--------------------This is a test of the operating system--------------------");
    kprintf("Loading GDT...");
    __gdt_init();
    kprintf("GDT Loaded Successfully...");
    while (1)
        ;
}