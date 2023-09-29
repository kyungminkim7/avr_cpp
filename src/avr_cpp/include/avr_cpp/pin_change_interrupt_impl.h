#include <avr/interrupt.h>
#include <avr/io.h>

#include "bit.h"

namespace avr_cpp {

etl::array<InterruptServiceRoutine, 3> PinChangeInterrupt::interruptServiceRoutines;

template<typename... Bits>
void PinChangeInterrupt::set(unsigned int interrupt, 
                             InterruptServiceRoutine interruptServiceRoutine, 
                             Bits... bits) {
    enableInterrupt(interrupt);
    interruptServiceRoutines[interrupt] = interruptServiceRoutine;
    setBitMask(interrupt, bits...);
}

void PinChangeInterrupt::enableInterrupt(unsigned int interrupt) {
    setBits(PCICR, interrupt);
}

template<typename... Bits>
void PinChangeInterrupt::setBitMask(unsigned int interrupt, Bits... bits) {
    switch (interrupt) {
        case PCIE0:
            setBits(PCMSK0, bits...);
            break;
        case PCIE1:
            setBits(PCMSK1, bits...);
            break;
        case PCIE2:
            setBits(PCMSK2, bits...);
            break;
    }
}

} // namespace avr_cpp

ISR(PCINT0_vect) {
    avr_cpp::PinChangeInterrupt::interruptServiceRoutines[PCIE0]();
}

ISR(PCINT1_vect) {
    avr_cpp::PinChangeInterrupt::interruptServiceRoutines[PCIE1]();
}

ISR(PCINT2_vect) {
    avr_cpp::PinChangeInterrupt::interruptServiceRoutines[PCIE2]();
}