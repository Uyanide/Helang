#include "power.h"

#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>

#include "helang.h"

static int _powerCon_impl(u8 flags[], size_t size, va_list* args) {
    printf("Flags: ");
    for (size_t i = 0; i < size; ++i) {
        printf("%d ", flags[i]);
    }
    printf("\nValue: %d\n", va_arg(*args, int));
    return 0;
}

HE_FUNC powerCon_impl = _powerCon_impl;
