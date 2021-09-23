#include "../include/types.h"

void puts(const char *str);

void kmain(void *multiboot_structure, uint32_t magicnumber)
{
    printk("--------------------This is a test of the operating system--------------------");
    while (1)
        ;
}

void printk(const char *str)
{
    uint16_t *vidmem = (uint16_t *)0xb8000;

    for (int i = 0; str[i] != '\0'; i++)
    {
        vidmem[i] = (vidmem[i] & 0xFF00) | str[i];
    }
}