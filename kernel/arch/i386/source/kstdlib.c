#include "../include/kstdlib.h"

void *kmemset(char *__restrict__ __dest, char __src, size_t __size)
{
    char *ret_block = __dest;

    while (__size--)
    {
        *__dest++ = __src;
    }
    __dest = NULL;
    return ret_block;
}

void *kmemcpy(char *__restrict__ __dest, char *__restrict__ __src, size_t __size)
{
    char *ret_block = __dest;

    while (__size--)
    {
        *__dest++ = *__src;
    }
    __dest = NULL;
    return ret_block;
}