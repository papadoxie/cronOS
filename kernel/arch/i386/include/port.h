// Defines the port interface

#pragma once

#include "types.h"

#ifndef __PORT_H__
#define __PORT_H__

//* Generic Port
struct __port_t
{
    uint16_t port_number;
    uint8_t *bandwidth;
};

//* 1 byte port
struct __port_b
{
    struct __port_t port_definition;
    uint8_t data;
};
// Read Write Functions for 1 byte ports
uint8_t __k_read_p(struct __port_b *port);
void __k_write_p(struct __port_b *port, uint8_t data);

//* 2 byte port
struct __port_w
{
    struct __port_t port_definition;
    uint16_t data;
};
// Read Write Functions for 2 byte ports
uint16_t __k_read_p(struct __port_w *port);
void __k_write_p(struct __port_w *port, uint16_t data);

//* 4 byte port
struct __port_d
{
    struct __port_t port_definition;
    uint32_t data;
};
// Read Write Functions for 4 byte ports
uint32_t __k_read_p(struct __port_d *port);
void __k_write_p(struct __port_d *port, uint32_t data);

#endif // __PORT_H__