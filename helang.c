#include "helang.h"

#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

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
        long val = strtol(p, &end, 10);
        if (p == end) {
            p++;
            continue;
        }
        flags[size++] = (u8)val;
        p             = end;
    }

    va_list args;
    va_start(args, flags_str);
    int result = func(flags, size, &args);
    va_end(args);

    free(flags);
    return result;
}

