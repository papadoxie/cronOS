// Defines the port interface

#pragma once

#include "types.h"

#ifndef __PORT_H__
#define __PORT_H__

#define k_write_p(PORT, DATA) _Generic((DATA),      \
                        uint8_t: writeb_p,          \
                        uint16_t: writew_p,         \
                        uint32_t: writel_p          \
                        )(DATA)

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

// Read Write Functions for 1 byte ports
uint32_t __k_read_p(struct __port_b *port);

#endif // __PORT_H__