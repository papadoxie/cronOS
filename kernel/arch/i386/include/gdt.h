#pragma once

#include "../include/types.h"

#ifndef __GDT_H__
#define __GDT_H__

#define GDT_BASE 0x00000800

struct __segment_descriptor
{
    uint16_t limit_lo;       // Lower 2 bytes of Segment Limit
    uint16_t base_lo;        // Lower 2 bytes of Base Address
    uint8_t base_hi;         // Upper byte of Base Address
    uint8_t flags;           // Flags (Access Rights)
    uint8_t limit_hi : 4;    // Upper 4 bits of Segment Limit
    uint8_t flags_extra : 4; // Upper 4 bits for Flags
    uint8_t base_vhi;        // Highest byte of Base Address
} __attribute__((packed));

typedef struct __global_descriptor_table
{
    uint32_t base_addr; // Complete Base Address
    uint16_t seg_limit; // Complete Segment Limit

    struct __segment_descriptor null; // Null Segment

    struct __segment_descriptor k_code;  // Kernel Code Segment
    struct __segment_descriptor k_data;  // Kernel Data Segment
    struct __segment_descriptor k_stack; // Kernel Stack Segment

    struct __segment_descriptor u_code;  // User Code Segment
    struct __segment_descriptor u_data;  // User Data Segment
    struct __segment_descriptor u_stack; // User Stack Segment

    struct __segment_descriptor tss; // Task State Segment

} GlobalDescriptorTable;

void gdt_init(GlobalDescriptorTable *gdt);
void gdt_destroy(GlobalDescriptorTable *gdt);

uint16_t cs_offset(GlobalDescriptorTable *gdt);
uint16_t ds_offset(GlobalDescriptorTable *gdt);

#endif