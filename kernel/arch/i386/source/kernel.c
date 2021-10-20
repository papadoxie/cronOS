#include <types.h>
#include <tty.h>
#include <kstdio.h>
#include <gdt.h>

__attribute__((noreturn)) void kmain(void *multiboot_structure, uint32_t magicnumber)
{
    //Initialize the tty
    __tty_init();
    kprintf("--------------------This is a test of the operating system--------------------\n");
    kprintf("Loading GDT...\n");
    
    //Initialize the GDT
    __gdt_init();
    kprintf("GDT Loaded Successfully...\n");
    


    // Never return
    end:
    goto end;
}