#include <gmock/gmock.h>

#include <avr/io.h>


#include <avr_cpp/matchers.h>
#include <avr_cpp/pin_change_interrupt.h>

using namespace ::testing;
using namespace avr_cpp;

void interruptServiceRoutine() {}

TEST(Set, EnablesInterrupt) {
    PCICR = 0;

    PinChangeInterrupt::set(PCIE1, 
        PinChangeInterrupt::InterruptServiceRoutine::create<interruptServiceRoutine>(),
        PC0);

    ASSERT_THAT(PCICR, BitsAreSet(PCIE1));
}

TEST(Set, SetsOneBitMaskBit) {
    PCMSK2 = 0;

    PinChangeInterrupt::set(PCIE2,
        PinChangeInterrupt::InterruptServiceRoutine::create<interruptServiceRoutine>(),
        PD2);

    ASSERT_THAT(PCMSK2, BitsAreSet(PD2));
}

TEST(Set, SetsMultipleBitMaskBits) {
    PCMSK1 = 0;

    PinChangeInterrupt::set(PCIE1, 
        PinChangeInterrupt::InterruptServiceRoutine::create<interruptServiceRoutine>(),
        PC0, PC3, PC5);

    ASSERT_THAT(PCMSK1, BitsAreSet(PC0, PC3, PC5));
}