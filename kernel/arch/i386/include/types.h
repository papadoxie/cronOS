#pragma once

#ifndef __TYPES_H__
#define __TYPES_H__

// 8 bit integers
typedef char int8_t;
typedef unsigned char uint8_t;

// 16 bit integers
typedef short int16_t;
typedef unsigned short uint16_t;

// 32 bit integers
typedef int int32_t;
typedef unsigned int uint32_t;

// 64 bit integers
typedef long long int64_t;
typedef unsigned long long uint64_t;

// Floating point types
typedef float float32_t;
typedef double float64_t;

// Unsigned char
typedef unsigned char uchar_t;

// size_t 32 bits
typedef unsigned int size_t;

// Boolean
typedef enum
{
    false = 0,
    true = !false
} bool_t;

#endif //__TYPES_H__