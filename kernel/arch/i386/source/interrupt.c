#include <interrupt.h>

uint32_t handle_interrupt(uint32_t interrupt_number, uint32_t esp)
{
    printk("Interrupt Caught");
    return esp;
}
