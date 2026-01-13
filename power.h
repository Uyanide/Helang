#ifndef HELANG_POWER_H
#define HELANG_POWER_H

#include "helang.h"

HE_DECLARE(powerCon_impl);

#define powerCon(flags, ...) HE_INVOKE(powerCon_impl, HE_FLAGS(flags), __VA_ARGS__)

#endif  // HELANG_POWER_H
