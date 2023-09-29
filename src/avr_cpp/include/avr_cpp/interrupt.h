#pragma once

#include <etl/delegate.h>

namespace avr_cpp {

using InterruptServiceRoutine = etl::delegate<void()>;

void enableInterrupts();
void disableInterrupts();

} // namespace avr_cpp