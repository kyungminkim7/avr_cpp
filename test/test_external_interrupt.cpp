#include <gmock/gmock.h>

#include <avr/io.h>

#include <avr_cpp/external_interrupt.h>
#include <avr_cpp_test/matchers.h>

using namespace ::testing;
using namespace avr_cpp;

void interruptServiceRoutine() {}

TEST(Set, EnablesInterrupt) {
    EIMSK = 0;

    ExternalInterrupt::set(INT0, ExternalInterrupt::Sense::Low,
                           InterruptServiceRoutine::create<interruptServiceRoutine>());

    ASSERT_THAT(EIMSK, BitsAreSet(INT0));
}

TEST(SetSense, Low) {
    EICRA = 0xFF;

    ExternalInterrupt::set(INT0, ExternalInterrupt::Sense::Low,
                           InterruptServiceRoutine::create<interruptServiceRoutine>());

    ASSERT_THAT(EICRA, BitsAreUnset(ISC01, ISC00));
}

TEST(SetSense, Change) {
    EICRA = 0;

    ExternalInterrupt::set(INT1, ExternalInterrupt::Sense::Change,
                           InterruptServiceRoutine::create<interruptServiceRoutine>());

    ASSERT_THAT(EICRA, BitsAreSet(ISC10));
}

TEST(SetSense, FallingEdge) {
    EICRA = 0;

    ExternalInterrupt::set(INT1, ExternalInterrupt::Sense::FallingEdge,
                           InterruptServiceRoutine::create<interruptServiceRoutine>());

    ASSERT_THAT(EICRA, BitsAreSet(ISC11));
}

TEST(SetSense, RisingEdge) {
    EICRA = 0;

    ExternalInterrupt::set(INT0, ExternalInterrupt::Sense::RisingEdge,
                           InterruptServiceRoutine::create<interruptServiceRoutine>());

    ASSERT_THAT(EICRA, BitsAreSet(ISC01, ISC00));
}
