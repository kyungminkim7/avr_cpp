#pragma once

#include <etl/delegate.h>

namespace avr_cpp {
namespace ExternalInterrupt {

using InterruptServiceRoutine = etl::delegate<void()>;

enum class Sense { Low, Change, FallingEdge, RisingEdge };

void set(unsigned int interrupt, Sense sense,
         InterruptServiceRoutine interruptServiceRoutine);

} // namespace ExternalInterrupt
} // namespace avr_cpp