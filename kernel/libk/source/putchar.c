#include <tty.h>
#include <kstdio.h>

int putchar(int __char)
{
    char c = __char;
    tty_write(&c, sizeof c);
    return __char;
}