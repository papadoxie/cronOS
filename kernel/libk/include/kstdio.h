#pragma once

#ifndef __K_IO_H__
#define __K_IO_H__

#include <types.h>
#include <sys/cdefs.h>

#define EOF -1
#define EOVERFLOW -149
#define EIO -3006

// Basic kernel prints
int printk(const char *__str);
int kprintf(const char *__restrict__ __fmt_str, ...);
int kputc(int __char);

#endif //__K_IO_H__