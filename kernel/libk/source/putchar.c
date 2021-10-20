#include <tty.h>
#include <kstdio.h>

int kputchar(int __char)
{
    char c = __char;
    __tty_write(&c, sizeof c);
    return __char;
}