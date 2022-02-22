#include <kstdio.h>
#include <kstdlib.h>

// Print a basic kernel error message and abort
__attribute__((__noreturn__)) void kpanic(const char *msg)
{
    printk(msg);
    abort();
}