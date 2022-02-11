#pragma once

#ifndef __IDT_H__
#define __IDT_H__

struct __idt
{
    unsigned short base_lo;
    unsigned short sel;
    unsigned char always0;
    unsigned char flags;
    unsigned short base_hi;
} __attribute__((packed));


#endif // __IDT_H__