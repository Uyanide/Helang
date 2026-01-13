#ifndef HELANG_HELANG_H
#define HELANG_HELANG_H

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "u8_complex.h"

#ifndef U8_COMPLEX_TYPE

typedef
#include "u8.h"
    u8;

u8 strtou8_l(const char* str, char** end);

u8 strtou8_ul(const char* str, char** end);

u8 strtou8_f(const char* str, char** end);

u8 strtou8_d(const char* str, char** end);

u8 strtou8_ll(const char* str, char** end);

u8 strtou8_ull(const char* str, char** end);

static const u8 HE_NULL = {};

#define strtou8(C, E)                    \
    _Generic((HE_NULL),                  \
        char: strtou8_l,                 \
        unsigned char: strtou8_ul,       \
        short: strtou8_l,                \
        unsigned short: strtou8_ul,      \
        int: strtou8_l,                  \
        unsigned int: strtou8_ul,        \
        long: strtou8_l,                 \
        unsigned long: strtou8_ul,       \
        long long: strtou8_ll,           \
        unsigned long long: strtou8_ull, \
        float: strtou8_f,                \
        double: strtou8_d)(C, E)

#endif

typedef int (*HE_FUNC)(u8 flags[], size_t size, va_list* args);

#define HE_FLAGS(x) #x

#define HE_DECLARE(name) extern HE_FUNC name;
#define HE_IMPLEMENT(name)                          \
    static int name##_impl(u8[], size_t, va_list*); \
    HE_FUNC name = name##_impl;                     \
    static int name##_impl(u8 flags[], size_t size, va_list* args)
#define HE_INVOKE(name, flags, ...) he_invoke(name, flags, __VA_ARGS__)

u8* he_parse_flags(const char* flags, size_t* size);

int he_invoke(HE_FUNC func, const char* flags, ...);

#endif  // HELANG_HELANG_H
