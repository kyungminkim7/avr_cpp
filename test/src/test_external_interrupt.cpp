#include <gmock/gmock.h>

#include <avr/io.h>

#include <avr_cpp/external_interrupt.h>
#include <avr_cpp_test/matchers.h>

using namespace ::testing;
using namespace avr_cpp;

namespace {

void interruptServiceRoutine() {}

} // namespace

TEST(ExternalInterrupt, Enable) {
    EIMSK = 0;

    ExternalInterrupt::set(INT0, ExternalInterrupt::Sense::Low,
                           InterruptServiceRoutine::create<interruptServiceRoutine>());

    ASSERT_THAT(EIMSK, BitsAreSet(INT0));
}

TEST(ExternalInterrupt, SetSenseLow) {
    EICRA = 0xFF;

    ExternalInterrupt::set(INT0, ExternalInterrupt::Sense::Low,
                           InterruptServiceRoutine::create<interruptServiceRoutine>());

    ASSERT_THAT(EICRA, BitsAreUnset(ISC01, ISC00));
}

TEST(ExternalInterrupt, SetSenseChange) {
    EICRA = 0;

    ExternalInterrupt::set(INT1, ExternalInterrupt::Sense::Change,
                           InterruptServiceRoutine::create<interruptServiceRoutine>());

    ASSERT_THAT(EICRA, BitsAreSet(ISC10));
}

TEST(ExternalInterrupt, SetSenseFallingEdge) {
    EICRA = 0;

    ExternalInterrupt::set(INT1, ExternalInterrupt::Sense::FallingEdge,
                           InterruptServiceRoutine::create<interruptServiceRoutine>());

    ASSERT_THAT(EICRA, BitsAreSet(ISC11));
}

TEST(ExternalInterrupt, SetSenseRisingEdge) {
    EICRA = 0;

    ExternalInterrupt::set(INT0, ExternalInterrupt::Sense::RisingEdge,
                           InterruptServiceRoutine::create<interruptServiceRoutine>());

    ASSERT_THAT(EICRA, BitsAreSet(ISC01, ISC00));
}
