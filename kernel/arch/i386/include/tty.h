#pragma once

#include <types.h>

#ifndef __TTY_H__
#define __TTY_H__

void tty_init(void);
void tty_putchar(char __c);
void tty_write(const char* __str, size_t __size);
void tty_writestr(const char* __str);

enum vga_color
{
    VGA_COLOR_BLACK = 0,
    VGA_COLOR_BLUE = 1,
    VGA_COLOR_GREEN = 2,
    VGA_COLOR_CYAN = 3,
    VGA_COLOR_RED = 4,
    VGA_COLOR_MAGENTA = 5,
    VGA_COLOR_BROWN = 6,
    VGA_COLOR_LIGHT_GREY = 7,
    VGA_COLOR_DARK_GREY = 8,
    VGA_COLOR_LIGHT_BLUE = 9,
    VGA_COLOR_LIGHT_GREEN = 10,
    VGA_COLOR_LIGHT_CYAN = 11,
    VGA_COLOR_LIGHT_RED = 12,
    VGA_COLOR_LIGHT_MAGENTA = 13,
    VGA_COLOR_LIGHT_BROWN = 14,
    VGA_COLOR_WHITE = 15,
};

static inline uint8_t tty_entry_color(enum vga_color fg_color, enum vga_color bg_color)
{
    return fg_color | bg_color << 4;
}

static inline uint16_t tty_entry(unsigned char uchar, uint8_t color)
{
    return (uint16_t) uchar | (uint16_t) color << 8;
}

#endif // __TTY_H__