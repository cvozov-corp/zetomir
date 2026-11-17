#ifndef ZETOMIR_TYPES_H
#define ZETOMIR_TYPES_H
typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned int       u32;
typedef unsigned long long u64;
typedef signed char        i8;
typedef signed int         i32;
typedef unsigned long      usize;
typedef __SIZE_TYPE__      size_t;
#define NULL ((void *)0)
#define PACKED __attribute__((packed))
#define UNUSED(x) ((void)(x))
#endif
