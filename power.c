#include "power.h"

#include <stdio.h>
#include <stdlib.h>

HE_IMPLEMENT(powerCon_impl) {
    printf("Flags: ");
    for (size_t i = 0; i < size; ++i) {
        printf("%d ", flags[i]);
    }
    printf("\nValue: %d\n", va_arg(*args, int));
    return 0;
}
