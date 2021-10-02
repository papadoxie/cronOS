// Defines the port interface

#pragma once

#include "types.h"

#ifndef __PORT_H__
#define __PORT_H__

//* Read Write Functions
// Use this to write to all types of ports
#define k_write_p(PORT, DATA) _Generic((DATA),      \
                        uint8_t: writeb_p,          \
                        uint16_t: writew_p,         \
                        uint32_t: writel_p          \
                        )(DATA)

// Read Function for ports
uint32_t __k_read_p(struct __port_b *port);

//* Generic Port
struct __port_t
{
    uint16_t port_number;
    uint8_t size;
};

//* 1 byte port
struct __port_b
{
    struct __port_t port_definition;
    uint8_t data;
};

//* 2 byte port
struct __port_w
{
    struct __port_t port_definition;
    uint16_t data;
};

//* 4 byte port
struct __port_d
{
    struct __port_t port_definition;
    uint32_t data;
};

#endif // __PORT_H__