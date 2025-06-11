#ifndef HELANG_POWER_H
#define HELANG_POWER_H

#include <stdarg.h>
#include <stddef.h>

#include "helang.h"

extern HE_FUNC powerCon_impl;

#define powerCon(flags, ...) he_invoke(powerCon_impl, HE_FLAGS(flags), __VA_ARGS__)

#endif  // HELANG_POWER_H