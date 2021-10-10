#pragma once

#include <types.h>

#ifndef __K_IO_H__
#define __K_IO_H__

// Start of the video memory
#define VIDEO_MEMORY 0xB8000

// Screen dimensions
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25

// Basic kernel print
void printk(const char *__str);

#endif //__K_IO_H__