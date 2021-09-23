#include "../include/types.h"
#include "../include/kstdlib.h"

void puts(const char *str);

void kmain(void *multiboot_structure, uint32_t magicnumber)
{
    printk("--------------------This is a test of the operating system--------------------");
    while (1)
        ;
}