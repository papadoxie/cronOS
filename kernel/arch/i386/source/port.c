#include <port.h>

uint8_t inb(uint16_t port_number)
{
    uint8_t ret;
    asm volatile("inb %1, %0"
                 : "=a"(ret)
                 : "Nd"(port_number));
    return ret;
}

uint8_t inw(uint16_t port_number)
{
    uint16_t ret;
    asm volatile("inw %1, %0"
                 : "=a"(ret)
                 : "Nd"(port_number));
    return ret;
}

uint8_t inl(uint16_t port_number)
{
    uint32_t ret;
    asm volatile("inl %1, %0"
                 : "=a"(ret)
                 : "Nd"(port_number));
    return ret;
}

uint8_t readb_p(struct __port_b *port_b)
{
    return inb(port_b->port.port_number);
}

uint16_t readw_p(struct __port_w *port_w)
{
    return inw(port_w->port.port_number);
}

uint32_t readl_p(struct __port_d *port_d)
{
    return inl(port_d->port.port_number);
}

void writeb_p(struct __port_b *port_b, uint8_t data)
{
    asm volatile("outb %0, %1"
                 :
                 : "a"(data), "Nd"(port_b->port.port_number));
}

void writew_p(struct __port_w *port_w, uint16_t data)
{
    asm volatile("outw %0, %1"
                 :
                 : "a"(data), "Nd"(port_w->port.port_number));
}

void writel_p(struct __port_d *port_d, uint32_t data)
{
    asm volatile("outl %0, %1"
                 :
                 : "a"(data), "Nd"(port_d->port.port_number));
}