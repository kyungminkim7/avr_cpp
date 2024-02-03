#pragma once

#include "interrupt.h"

namespace avr_cpp {
namespace ExternalInterrupt {

enum class Sense { Low, Change, FallingEdge, RisingEdge };

void set(unsigned int interrupt, Sense sense,
         InterruptServiceRoutine interruptServiceRoutine);

} // namespace ExternalInterrupt
} // namespace avr_cpp