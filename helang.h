#ifndef HELANG_HELANG_H
#define HELANG_HELANG_H

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

typedef uint8_t u8;

typedef int (*HE_FUNC)(u8 flags[], size_t size, va_list* args);

#define HE_FLAGS(x) #x

u8* he_parse_flags(const char* flags, size_t* size);

int he_invoke(HE_FUNC func, const char* flags, ...);

#endif  // HELANG_HELANG_H
