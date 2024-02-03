#include <gmock/gmock.h>

#include <avr/io.h>

#include <avr_cpp/pulse_width_modulation.h>
#include <avr_cpp_test/matchers.h>

using namespace ::testing;
using namespace avr_cpp;

TEST(Construction, SetsFastPWMMode) {
    TCCR0A = 0;
    TCCR0B = 0xFF;
    
    PulseWidthModulation0_1 pwm(Timer::Channel::B);

    ASSERT_THAT(TCCR0A, BitsAreSet(WGM01, WGM00));
    ASSERT_THAT(TCCR0B, BitsAreUnset(WGM02));
}

TEST(SetNonInvertingCompareOutputMode, One) {
    TCCR2A = 0;
    setBits(TCCR2A, COM2A0);

    PulseWidthModulation2_8 pwm(Timer::Channel::A);

    ASSERT_THAT(TCCR2A, BitsAreUnset(COM2A0));
    ASSERT_THAT(TCCR2A, BitsAreSet(COM2A1));
}

TEST(SetNonInvertingCompareOutputMode, Multiple) {
    TCCR0A = 0;
    setBits(TCCR0A, COM0A0);
    setBits(TCCR0A, COM0B0);

    PulseWidthModulation0_256 pwm(Timer::Channel::A | Timer::Channel::B);

    ASSERT_THAT(TCCR0A, BitsAreUnset(COM0A0));
    ASSERT_THAT(TCCR0A, BitsAreSet(COM0A1));

    ASSERT_THAT(TCCR0A, BitsAreUnset(COM0B0));
    ASSERT_THAT(TCCR0A, BitsAreSet(COM0B1));
}

TEST(SetDutyCycle, OneChannel) {
    OCR2B = 0;
    PulseWidthModulation2_1024 pwm(Timer::Channel::B);

    pwm.set(115);

    ASSERT_THAT(OCR2B, Eq(115));
}

TEST(SetDutyCycle, MultipleChannels) {
    OCR0A = 0;
    OCR0B = 0;
    PulseWidthModulation0_1024 pwm(Timer::Channel::A | Timer::Channel::B);

    pwm.set(112);

    ASSERT_THAT(OCR0A, Eq(112));
    ASSERT_THAT(OCR0B, Eq(112));
}

TEST(SetDutyCycle, SelectChannel) {
    OCR0A = 0;
    OCR0B = 0;
    PulseWidthModulation0_1024 pwm(Timer::Channel::A | Timer::Channel::B);

    pwm.set(112, Timer::Channel::B);

    ASSERT_THAT(OCR0A, Eq(0));
    ASSERT_THAT(OCR0B, Eq(112));
}

TEST(StartSetsClockPrescaler, One) {
    TCCR0B = 0;
    setBits(TCCR0B, CS02, CS01);

    PulseWidthModulation0_1 pwm(Timer::Channel::A);
    pwm.start();

    ASSERT_THAT(TCCR0B, BitsAreSet(CS00));
    ASSERT_THAT(TCCR0B, BitsAreUnset(CS02, CS01));
}

TEST(StartSetsClockPrescaler, Eight) {
    TCCR2B = 0;
    setBits(TCCR2B, CS22, CS20);

    PulseWidthModulation2_8 pwm(Timer::Channel::A);
    pwm.start();

    ASSERT_THAT(TCCR2B, BitsAreSet(CS21));
    ASSERT_THAT(TCCR2B, BitsAreUnset(CS22, CS20));
}

TEST(Stop, ClearsClockSelectBits) {
    PulseWidthModulation2_1024 pwm(Timer::Channel::A);
    pwm.start();

    pwm.stop();

    ASSERT_THAT(TCCR2B, BitsAreUnset(CS22, CS21, CS20));
}

class Destruction : public Test {
public:
    Destruction() {
        PulseWidthModulation2_1024 pwm(Timer::Channel::A | Timer::Channel::B);
        pwm.start();
    }
};

TEST(Destruction, StopsPwm) {
    ASSERT_THAT(TCCR2B, BitsAreUnset(CS22, CS21, CS20));
}

TEST(Destruction, DisconnectsOutputComparePins) {
    ASSERT_THAT(TCCR2A, BitsAreUnset(COM2A1, COM2A0, COM2B1, COM2B0));
}