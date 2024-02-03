#pragma once

#include <etl/array.h>

#include "interrupt.h"

namespace avr_cpp {

class PinChangeInterrupt {
public:
    static etl::array<InterruptServiceRoutine, 3> interruptServiceRoutines;

    template<typename... Bits>
    static void set(unsigned int interrupt, 
                    InterruptServiceRoutine interruptServiceRoutine,
                    Bits... bits);

private:
    static void enableInterrupt(unsigned int interrupt);

    template<typename... Bits>
    static void setBitMask(unsigned int interrupt, Bits... bits);
};

} // namespace avr_cpp

#include "pin_change_interrupt_impl.h"