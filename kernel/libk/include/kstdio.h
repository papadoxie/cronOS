#pragma once

#include <types.h>

#ifndef __K_IO_H__
#define __K_IO_H__

#define EOF -1
#define EOVERFLOW -149
#define EIO -3006

// Basic kernel prints
int printk(const char *__str);
int kprintf(const char *__restrict__ __fmt_str, ...);
int kputc(int __char);

#endif //__K_IO_H__