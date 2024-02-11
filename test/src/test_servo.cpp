#include <gmock/gmock.h>

#include <avr/io.h>

#include <avr_cpp/angle.h>
#include <avr_cpp/bit.h>
#include <avr_cpp/servo.h>
#include <avr_cpp/timer.h>
#include <avr_cpp_test/matchers.h>

using namespace ::testing;
using namespace avr_cpp;

TEST(Servo, ConstructorSetsFastPWMInputCaptureMode) {
    TCCR1A = 0;
    setBits(TCCR1A, WGM10);

    Servo1 servo(Timer::Channel::B);

    ASSERT_THAT(TCCR1A, BitsAreUnset(WGM10));
    ASSERT_THAT(TCCR1A, BitsAreSet(WGM11));
    ASSERT_THAT(TCCR1B, BitsAreSet(WGM13, WGM12));
}

TEST(Servo, SetClockPrescalerOneMicrosecondResolution) {
    TCCR1B = 0;

    Servo1 servo(Timer::Channel::A);

    ASSERT_THAT(TCCR1B, AnyOf(BitsAreSet(CS12), 
                              BitsAreSet(CS11), 
                              BitsAreSet(CS10)));
}

TEST(Servo, SetsInputCaptureRegisterToPeriod) {
    const auto MIN_PULSE = Chrono::Milliseconds(1);
    const auto MAX_PULSE = Chrono::Milliseconds(2);
    ICR1 = 0;

    Servo1 servo(Timer::Channel::A, 
                 MIN_PULSE, MAX_PULSE, 
                 Chrono::Milliseconds(15));

    ASSERT_THAT(ICR1, Eq(15'000));
}

TEST(Servo, ContructorEnableChannel) {
    TCCR1A = 0;
    setBits(TCCR1A, COM1B0);

    Servo1 servo(Timer::Channel::B);

    ASSERT_THAT(TCCR1A, BitsAreUnset(COM1B0));
    ASSERT_THAT(TCCR1A, BitsAreSet(COM1B1));
}

TEST(Servo, ConstructorEnableMultipleChannels) {
    TCCR1A = 0;
    setBits(TCCR1A, COM1A0, COM1B0);

    Servo1 servo(Timer::Channel::A | Timer::Channel::B);

    ASSERT_THAT(TCCR1A, BitsAreUnset(COM1A0, COM1B0));
    ASSERT_THAT(TCCR1A, BitsAreSet(COM1B1, COM1B1));
}

class ServoSetPosition : public Test {
public:
    static constexpr Chrono::Microseconds MIN_PULSE{991};
    static constexpr Chrono::Microseconds MAX_PULSE{1994};
    static constexpr Chrono::Milliseconds PERIOD{2};
    static const Degree<float> MIN_ANGLE;
    static const Degree<float> MAX_ANGLE;

    Servo1 servo{Timer::Channel::A | Timer::Channel::B, 
                 MIN_PULSE, MAX_PULSE, PERIOD, MIN_ANGLE, MAX_ANGLE};

    ServoSetPosition() {
        OCR1A = 0;
        OCR1B = 0;
    }
};

const Degree<float> ServoSetPosition::MIN_ANGLE = 18.0f;
const Degree<float> ServoSetPosition::MAX_ANGLE = 178.0f;

TEST_F(ServoSetPosition, Min) {
    servo.setPosition(MIN_ANGLE, Timer::Channel::B);

    ASSERT_THAT(OCR1B, Eq(MIN_PULSE.count()));
}

TEST_F(ServoSetPosition, Max) {
    servo.setPosition(MAX_ANGLE, Timer::Channel::B);

    ASSERT_THAT(OCR1B, Eq(MAX_PULSE.count()));
}

TEST_F(ServoSetPosition, Mid) {
    const auto midAngle = MIN_ANGLE + (MAX_ANGLE - MIN_ANGLE) / 2;
    const auto midPulse = MIN_PULSE.count() + 
        (MAX_PULSE.count() - MIN_PULSE.count()) / 2;

    servo.setPosition(midAngle, Timer::Channel::A);

    ASSERT_THAT(OCR1A, Eq(midPulse));
}

TEST_F(ServoSetPosition, OutOfBoundsLower) {
    servo.setPosition(MIN_ANGLE - 1,
                      Timer::Channel::A);

    ASSERT_THAT(OCR1A, Eq(MIN_PULSE.count()));
}

TEST_F(ServoSetPosition, OutOfBoundsUpper) {
    servo.setPosition(MAX_ANGLE + 1,
                      Timer::Channel::A);

    ASSERT_THAT(OCR1A, Eq(MAX_PULSE.count()));
}

TEST_F(ServoSetPosition, OneChannel) {
    servo.setPosition(MAX_ANGLE, Timer::Channel::A);

    ASSERT_THAT(OCR1B, Eq(0));
}

TEST_F(ServoSetPosition, DefaultChannels) {
    servo.setPosition(MAX_ANGLE);

    ASSERT_THAT(OCR1A, Gt(0));
    ASSERT_THAT(OCR1B, Gt(0));
}
