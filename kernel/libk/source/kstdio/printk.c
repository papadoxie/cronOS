#include <kstdio.h>

int printk(const char * __str)
{
    return kprintf("%s\n", __str);
}