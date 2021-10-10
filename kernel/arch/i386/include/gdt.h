#pragma once

#include <types.h>
#include <kstdlib.h>

#ifndef __GDT_H__
#define __GDT_H__

//* Segment Base and Limits
#define SEG_BASE_ADDR 0x0       // Base Address of Segment
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

//* GDT Registry
struct __gdt_r
{
    uint32_t base; // Base Address of GDT
    uint16_t size; // Size of GDT
} __attribute__((packed));

//* Segment Descriptor
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

//* Global Descriptor Table
#define GDT_BASE 0x00000800

struct __global_descriptor_table
{
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

    //* GDT Registry Instance
    struct __gdt_r gdtr;
};

//* GDT Functions
void __gdt_init(void);
void __gdt_destroy(void);

//* Get Kernel Segment Offsets from GDT Base
uint16_t __get_k_cs_offset(void);
uint16_t __get_k_ds_offset(void);
uint16_t __get_k_ss_offset(void);

//* Get User Segment Offsets from GDT Base
uint16_t __get_u_cs_offset(void);
uint16_t __get_u_ds_offset(void);
uint16_t __get_u_ss_offset(void);

#endif //__GDT_H__