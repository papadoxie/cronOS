#include <kstdlib.h>

void *kmemset(char *__dest, char __src, size_t __size)
{
    char *ret_block = __dest;

    while (__size--)
    {
        *__dest++ = __src;
    }
    return ret_block;
}

void *kmemcpy(char *__dest, char *__src, size_t __size)
{
    char *ret_block = __dest;

    while (__size--)
    {
        *__dest++ = *__src++;
    }
    return ret_block;
}