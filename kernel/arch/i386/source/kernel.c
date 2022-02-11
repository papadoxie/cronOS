#include <types.h>
#include <tty.h>
#include <kstdio.h>
#include <gdt.h>

__attribute__((noreturn)) void kmain(void *multiboot_structure, uint32_t magicnumber)
{
    //Initialize the tty
    __tty_init();
    printk("--------------------This is a test of the operating system--------------------");

    //Using arguments to suppress werror
    kprintf("Multiboot Structure: %s\n", (uint32_t)multiboot_structure);
    kprintf("Magic Number: %s\n", magicnumber);

    //Initialize the GDT
    printk("Loading GDT...");
    __gdt_init();
    printk("GDT Loaded Successfully...");

// Never return
end:
    goto end;
}
