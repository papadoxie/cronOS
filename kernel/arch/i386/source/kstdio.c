#include "../include/kstdio.h"

void printk(const char *__str)
{
    uint16_t *vidmem = (uint16_t *)0xb8000;

    for (uint16_t i = 0; __str[i] != '\0'; i++)
    {
        vidmem[i] = (vidmem[i] & 0xFF00) | __str[i];
    }
}