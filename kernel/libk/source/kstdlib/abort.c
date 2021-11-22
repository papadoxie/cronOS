#include <kstdio.h>
#include <kstdlib.h>

__attribute__((__noreturn__)) void abort(void)
{
    printk("Kernel: Panic: abort() called");
    
    while (1)
    {
        __builtin_unreachable();
    }
}