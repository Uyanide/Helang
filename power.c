#include "power.h"

#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>

#include "helang.h"

HE_IMPLEMENT(powerCon_func) {
    printf("Flags: ");
    for (size_t i = 0; i < size; ++i) {
        printf("%d ", flags[i]);
    }
    printf("\nValue: %d\n", va_arg(*args, int));
    return 0;
}
