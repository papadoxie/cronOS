#include "../include/port.h"

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

uint32_t __k_read_p(struct __port_b *port)
{
    uint32_t ret;
    if (port->port_definition.size == 8)
    {
        ret = inb(port->port_definition.port_number);
        return ret;
    }

    if (port->port_definition.size == 16)
    {
        ret = inw(port->port_definition.port_number);
        return ret;
    }

    if (port->port_definition.size == 32)
    {
        ret = inl(port->port_definition.port_number);
        return ret;
    }
    return NULL;
}

void writeb_p(struct __port_b *port, uint8_t data)
{
    asm volatile("outb %0, %1"
                 :
                 : "a"(data), "Nd"(port->port_definition.port_number));
}

void writew_p(struct __port_b *port, uint16_t data)
{
    asm volatile("outw %0, %1"
                 :
                 : "a"(data), "Nd"(port->port_definition.port_number));
}

void writel_p(struct __port_b *port, uint32_t data)
{
    asm volatile("outl %0, %1"
                 :
                 : "a"(data), "Nd"(port->port_definition.port_number));
}