#pragma once

#include "types.h"

#ifndef __GDT_H__
#define __GDT_H__

//* Segment Base and Limits
#define BASE_ADDR 0x0           // Base Address of Segment
#define SEG_LIMIT_CS 0xf0000000 // Segment Limit of Code Segment
#define SEG_LIMIT_DS 0xf0000000 // Segment Limit of Data Segment
#define SEG_LIMIT_SS 0x0        // Segment Limit of Stack Segment

//* Access Bits
#define ACS_PRESENT 0x80   // Present Bit
#define ACS_R0 0x00        // Privilege Level 0
#define ACS_R1 0x20        // Privilege Level 1
#define ACS_R2 0x40        // Privilege Level 2
#define ACS_R3 0x60        // Privilege Level 3
#define ACS_SEG 0x10       // Segment Bit
#define ACS_X 0x08         // Executable Bit
#define ACS_DIRECTION 0x04 // Direction Bit
#define ACS_RW 0x02        // Read/Write Bit
#define ACS_ACCESS 0x01    // Accessed Bit

//* Flags
#define FLG_GB 0x08   // 4 KiB limit multiplier
#define FLG_SB 0x04   // 32 bit protected mode
#define FLG_LONG 0x02 // Long Mode
#define FLG_AVBL 0x01 // For programmer use

struct __segment_descriptor
{
    uint16_t limit_lo;    // Lower 2 bytes of Segment Limit
    uint16_t base_lo;     // Lower 2 bytes of Base Address
    uint8_t base_hi;      // Upper byte of Base Address
    uint8_t access;       // Access Rights and Segment Type
    uint8_t limit_hi : 4; // Upper 4 bits of Segment Limit
    uint8_t flags : 4;    // Segment size unit and 16/32 bit
    uint8_t base_vhi;     // Highest byte of Base Address
} __attribute__((packed));

typedef struct __global_descriptor_table
{
    uint32_t base_addr; // Complete Base Address
    uint16_t seg_limit; // Complete Segment Size

    //* Null Segment
    struct __segment_descriptor null;

    //* Kernelmode Segments
    struct __segment_descriptor k_cs; // Kernel Code Segment
    struct __segment_descriptor k_ds; // Kernel Data Segment
    struct __segment_descriptor k_ss; // Kernel Stack Segment

    //* Usermode Segments
    struct __segment_descriptor u_cs; // Code Segment
    struct __segment_descriptor u_ds; // Data Segment
    struct __segment_descriptor u_ss; // Stack Segment

    //* Task State Segments
    struct __segment_descriptor m_tss;  // Multitask Handling
    struct __segment_descriptor df_tss; // Double Fault Handling

} GlobalDescriptorTable;

//* GDT Functions
void gdt_init(GlobalDescriptorTable *gdt);
void gdt_destroy(GlobalDescriptorTable *gdt);

uint16_t get_cs_offset(GlobalDescriptorTable *gdt); 
uint16_t get_ds_offset(GlobalDescriptorTable *gdt);

#endif //__GDT_H__