/*
 * ESPRESSIF MIT License
 *
 * Copyright (c) 2016 <ESPRESSIF SYSTEMS (SHANGHAI) PTE LTD>
 *
 * Permission is hereby granted for use on ESPRESSIF SYSTEMS ESP8266 only, in which case,
 * it is free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished
 * to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Replacement for the original c_types.h header in C:\Espressif\ESP8266_SDK\include that provides the following
 * improvements and enhancements:
 * - Guards enabling this header to be used with -std=gnu99 compiler option and <stdint.h> and <stdbool.h> headers
 *
 */

#ifndef _C_TYPES_H_
#define _C_TYPES_H_

#ifndef _STDINT_H
typedef unsigned char       uint8_t;
#endif
typedef signed char         sint8_t;
#ifndef _STDINT_H
typedef signed char         int8_t;
typedef unsigned short      uint16_t;
#endif
typedef signed short        sint16_t;
#ifndef _STDINT_H
typedef signed short        int16_t;
typedef unsigned int        uint32_t;
#endif
typedef signed int          sint32_t;
#ifndef _STDINT_H
typedef signed int          int32_t;
#endif
typedef signed long long    sint64_t;
#ifndef _STDINT_H
typedef unsigned long long  uint64_t;
#endif
#ifndef _SYS_TYPES_H 
typedef unsigned long long  u_int64_t;
#endif
typedef float               real32_t;
typedef double              real64_t;

typedef unsigned char       uint8;
typedef unsigned char       u8;
typedef signed char         sint8;
typedef signed char         int8;
typedef signed char         s8;
typedef unsigned short      uint16;
typedef unsigned short      u16;
typedef signed short        sint16;
typedef signed short        s16;
typedef unsigned int        uint32;
typedef unsigned int        u_int;
typedef unsigned int        u32;
typedef signed int          sint32;
typedef signed int          s32;
typedef int                 int32;
typedef signed long long    sint64;
typedef unsigned long long  uint64;
typedef unsigned long long  u64;
typedef float               real32;
typedef double              real64;

#define __le16      u16

#ifndef _SIZE_T_DEFINED
#if !defined(__size_t)
#define __size_t            (1)
typedef unsigned int        size_t;
#endif
#endif

#ifndef __packed
#define __packed        __attribute__((packed))
#endif

#define LOCAL       static

#ifndef NULL
#define NULL (void *)0
#endif /* NULL */

/* probably should not put STATUS here */
typedef enum {
    OK = 0,
    FAIL,
    PENDING,
    BUSY,
    CANCEL,
} STATUS;

#define BIT(nr)                 (1UL << (nr))

#define REG_SET_BIT(_r, _b)  (*(volatile uint32_t*)(_r) |= (_b))
#define REG_CLR_BIT(_r, _b)  (*(volatile uint32_t*)(_r) &= ~(_b))

#define DMEM_ATTR __attribute__((section(".bss")))
#define SHMEM_ATTR

#ifdef ICACHE_FLASH
#define ICACHE_FLASH_ATTR __attribute__((section(".irom0.text")))
#define ICACHE_RODATA_ATTR __attribute__((section(".irom.text")))
#else
#define ICACHE_FLASH_ATTR
#define ICACHE_RODATA_ATTR
#endif /* ICACHE_FLASH */

#define STORE_ATTR __attribute__((aligned(4)))

#ifndef __cplusplus

#ifndef bool
typedef unsigned char   bool;
#endif
#define BOOL            bool
#ifndef true
#define true            (1)
#endif
#ifndef false
#define false           (0)
#endif
#define TRUE            true
#define FALSE           false


#endif /* !__cplusplus */

#endif /* _C_TYPES_H_ */
