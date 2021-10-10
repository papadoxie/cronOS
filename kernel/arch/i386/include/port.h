// Defines the port interface

#pragma once

#include <types.h>

#ifndef __PORT_H__
#define __PORT_H__

//* Read Write Functions
// Use these to read and write to all kinds of ports
#define __k_write_p(PORT, DATA) _Generic((PORT),    \
                        struct __port_b: writeb_p,  \
                        struct __port_w: writew_p,  \
                        struct __port_d: writel_p   \
                        )(DATA)

#define __k_read_p(PORT) _Generic((PORT),           \
                        struct __port_b: readb_p,   \
                        struct __port_w: readw_p,   \
                        struct __port_d: readl_p    \
                        )(PORT)

//* Generic Port
struct __port_t
{
    uint16_t port_number;
    uint8_t size;
};

//* 1 byte port
struct __port_b
{
    struct __port_t port;
    uint8_t data;
};

//* 2 byte port
struct __port_w
{
    struct __port_t port;
    uint16_t data;
};

//* 4 byte port
struct __port_d
{
    struct __port_t port;
    uint32_t data;
};

#endif // __PORT_H__