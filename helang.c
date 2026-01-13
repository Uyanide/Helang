#include "helang.h"

#include <string.h>

#ifndef U8_COMPLEX_TYPE

u8 strtou8_l(const char* str, char** end) {
    return (u8)strtol(str, end, 10);
}

u8 strtou8_ul(const char* str, char** end) {
    return (u8)strtoul(str, end, 10);
}

u8 strtou8_f(const char* str, char** end) {
    return (u8)strtof(str, end);
}

u8 strtou8_d(const char* str, char** end) {
    return (u8)strtod(str, end);
}

u8 strtou8_ll(const char* str, char** end) {
    return (u8)strtoll(str, end, 10);
}

u8 strtou8_ull(const char* str, char** end) {
    return (u8)strtoull(str, end, 10);
}

#endif

const u8 HE_NULL = {0};

int he_invoke(HE_FUNC func, const char* flags_str, ...) {
    // Calculate number of flags
    size_t cap    = 1;
    const char* p = flags_str;
    while (*p) cap += (*p++ == '|');

    // NO VLA, no
    u8* flags   = (u8*)malloc(sizeof(u8) * cap);
    size_t size = 0;

    p = flags_str;
    char* end;
    while (*p) {
        if (*p == '|' || *p == ' ') {
            p++;
            continue;
        }
        u8 val = strtou8(p, &end);
        if (p == end) {
            p++;
            continue;
        }
        flags[size++] = val;
        p             = end;
    }

    va_list args;
    va_start(args, flags_str);
    int result = func(flags, size, &args);
    va_end(args);

    free(flags);
    return result;
}

