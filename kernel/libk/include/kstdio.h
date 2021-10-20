#pragma once

#include <types.h>

#ifndef __K_IO_H__
#define __K_IO_H__

#define EOF -1
#define EOVERFLOW -1
#define EIO -1

// Basic kernel prints
void printk(const char *__str);
int kprintf(const char *__restrict__ __fmt_str, ...);
int putchar(int __char);

#endif //__K_IO_H__