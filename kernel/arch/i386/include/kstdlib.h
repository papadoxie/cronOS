#pragma once

#include "types.h"

#ifndef __K_STD_LIB_H__
#define __K_STD_LIB_H__

void *kmemset(char *__restrict__ __dest, char __src, size_t __size);
void *kmemcpy(char *__restrict__ __dest, char *__restrict__ __src, size_t __size);

#endif //__K_STD_LIB_H__