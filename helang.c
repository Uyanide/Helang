#include "helang.h"

#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

static const size_t FLAGS_CAP_INIT = 10;
static const size_t FLAGS_CAP_FACT = 2;

u8* he_parse_flags(const char* flags, size_t* size) {
    u8* ret     = NULL;
    char* cpy   = strdup(flags);
    char* token = strtok(cpy, "|");
    size_t cap  = 0;
    do {
        while (*size >= cap) {
            cap = cap ? cap * FLAGS_CAP_FACT : FLAGS_CAP_INIT;
            ret = (u8*)realloc(ret, sizeof(u8) * (cap));
        }
        ret[(*size)++] = (u8)atoi(token);
    } while ((token = strtok(NULL, "|")) != NULL);
    free(cpy);
    return ret;
}

int he_invoke(HE_FUNC func, const char* flags, ...) {
    size_t size     = 0;
    u8* parsedFlags = he_parse_flags(flags, &size);
    va_list args;
    va_start(args, flags);
    int result = func(parsedFlags, size, args);
    va_end(args);
    free(parsedFlags);
    return result;
}
