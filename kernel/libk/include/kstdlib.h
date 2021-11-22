#pragma once

#ifndef __K_STD_LIB_H__
#define __K_STD_LIB_H__

#include <types.h>
#include <sys/cdefs.h>

void *kmemset(char *__restrict__ __dest, char __src, size_t __size);
void *kmemcpy(char *__restrict__ __dest, char *__restrict__ __src, size_t __size);

__attribute__((__noreturn__)) void abort(void);

#endif //__K_STD_LIB_H__