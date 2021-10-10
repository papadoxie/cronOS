#pragma once

#include <types.h>
#include <port.h>
#include <kstdio.h>

#ifndef __INT_H__
#define __INT_H__

uint32_t __handle_interrupt(uint32_t interrupt_number, uint32_t esp);

//* Interrupt Request Handlers
void __ireq_handler_0x00(uint32_t esp); // Timer Interrupt
void __ireq_handler_0x01(uint32_t esp); // Keyboard Interrupt

struct __gate_descriptor
{
    uint16_t offset_low;
    uint16_t cs_gdt;
    uint8_t zero;
    uint8_t type_attr;
    uint16_t offset_high;
} __attribute__((packed));

#endif // __INT_H__