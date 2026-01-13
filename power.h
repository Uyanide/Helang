#ifndef HELANG_POWER_H
#define HELANG_POWER_H

#include <stdarg.h>
#include <stddef.h>

#include "helang.h"

HE_INTERFACE(powerCon_func);

#define powerCon(flags, ...) he_invoke(powerCon_func, HE_FLAGS(flags), __VA_ARGS__)

#endif  // HELANG_POWER_H
