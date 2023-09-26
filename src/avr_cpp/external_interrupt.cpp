#include <avr_cpp/external_interrupt.h>

#include <avr/interrupt.h>
#include <avr/io.h>
#include <etl/array.h>

#include <avr_cpp/bit_op.h>

namespace {

using namespace avr_cpp;

etl::array<ExternalInterrupt::InterruptServiceRoutine, 2> interruptServiceRoutines;

void setSenseControl(unsigned int interrupt, ExternalInterrupt::Sense sense) {
    static constexpr auto NUM_CONTROL_BITS_PER_INTERRUPT = 2;
    const auto bitShift = interrupt * NUM_CONTROL_BITS_PER_INTERRUPT;

    EICRA &= ~(createBitMask<uint8_t>(ISC01, ISC00) << bitShift);

    switch (sense) {
    case ExternalInterrupt::Sense::Low:
        break;

    case ExternalInterrupt::Sense::Change:
        EICRA |= (createBitMask<uint8_t>(ISC00) << bitShift);
        break;

    case ExternalInterrupt::Sense::FallingEdge:
        EICRA |= (createBitMask<uint8_t>(ISC01) << bitShift);
        break;

    case ExternalInterrupt::Sense::RisingEdge:
        EICRA |= (createBitMask<uint8_t>(ISC01, ISC00) << bitShift);
        break;
    
    default:
        break;
    }
}

void enableInterrupt(unsigned int interrupt) {
    setBits(EIMSK, interrupt);
}

} // namespace

ISR(INT0_vect) {
    interruptServiceRoutines[INT0]();
}

ISR(INT1_vect) {
    interruptServiceRoutines[INT1]();
}

namespace avr_cpp {
namespace ExternalInterrupt {

void set(unsigned int interrupt, Sense sense, 
         InterruptServiceRoutine interruptServiceRoutine) {
    setSenseControl(interrupt, sense);
    enableInterrupt(interrupt);
    interruptServiceRoutines[interrupt] = interruptServiceRoutine;
}

} // namespace ExternalInterrupt
} // namespace avr_cpp