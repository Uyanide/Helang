#if 0

#ifndef HELANG_U8_COMPLEX_H
#define HELANG_U8_COMPLEX_H

#define U8_COMPLEX_TYPE

typedef struct {
    double real;
    double imag;
} u8;

u8 strtou8(const char* str, char** end);

#endif  // HELANG_U8_COMPLEX_H

#endif
