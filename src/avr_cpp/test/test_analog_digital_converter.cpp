#include <gmock/gmock.h>

#include <avr/io.h>

#include <avr_cpp/analog_digital_converter.h>
#include <avr_cpp/bit_op.h>
#include <avr_cpp/matchers.h>

using namespace ::testing;
using namespace avr_cpp;

class SetVoltageReference : public Test {
public:
    static constexpr auto CLOCK_PRESCALER = AnalogDigitalConverter::ClockPrescaler::Two;

    void SetUp() override {
        ADMUX = 0;
    }
};

TEST_F(SetVoltageReference, AREF) {
    ADMUX = 0xFF;

    AnalogDigitalConverter adc(AnalogDigitalConverter::VoltageReference::AREF,
                               CLOCK_PRESCALER);

    ASSERT_THAT(ADMUX, BitsAreUnset(REFS1, REFS0));
}

TEST_F(SetVoltageReference, AVCC) {
    AnalogDigitalConverter adc(AnalogDigitalConverter::VoltageReference::AVCC,
                               CLOCK_PRESCALER);

    ASSERT_THAT(ADMUX, Eq(createBitMask<uint8_t>(REFS0)));
}

TEST_F(SetVoltageReference, Internal1_1V) {
    AnalogDigitalConverter adc(AnalogDigitalConverter::VoltageReference::Internal1_1V,
                               CLOCK_PRESCALER);

    ASSERT_THAT(ADMUX, Eq(createBitMask<uint8_t>(REFS1, REFS0)));
}

class SetClockPrescaler: public Test {
public:
    static constexpr auto VOLTAGE_REFERENCE = AnalogDigitalConverter::VoltageReference::AVCC;

    void SetUp() override {
        ADCSRA = 0;
    }
};

TEST_F(SetClockPrescaler, Two) {
    ADCSRA = 0xFF;

    AnalogDigitalConverter adc(VOLTAGE_REFERENCE,
                               AnalogDigitalConverter::ClockPrescaler::Two);

    ASSERT_THAT(ADCSRA, BitsAreUnset(ADPS2, ADPS1, ADPS0));
}

TEST_F(SetClockPrescaler, Four) {
    AnalogDigitalConverter adc(VOLTAGE_REFERENCE,
                               AnalogDigitalConverter::ClockPrescaler::Four);

    ASSERT_THAT(ADCSRA, Eq(createBitMask<uint8_t>(ADPS1)));
}

TEST_F(SetClockPrescaler, Eight) {
    AnalogDigitalConverter adc(VOLTAGE_REFERENCE,
                               AnalogDigitalConverter::ClockPrescaler::Eight);

    ASSERT_THAT(ADCSRA, Eq(createBitMask<uint8_t>(ADPS1, ADPS0)));
}

TEST_F(SetClockPrescaler, Sixteen) {
    AnalogDigitalConverter adc(VOLTAGE_REFERENCE,
                               AnalogDigitalConverter::ClockPrescaler::Sixteen);

    ASSERT_THAT(ADCSRA, Eq(createBitMask<uint8_t>(ADPS2)));
}

TEST_F(SetClockPrescaler, ThirtyTwo) {
    AnalogDigitalConverter adc(VOLTAGE_REFERENCE,
                               AnalogDigitalConverter::ClockPrescaler::ThirtyTwo);

    ASSERT_THAT(ADCSRA, Eq(createBitMask<uint8_t>(ADPS2, ADPS0)));
}

TEST_F(SetClockPrescaler, SixtyFour) {
    AnalogDigitalConverter adc(VOLTAGE_REFERENCE,
                               AnalogDigitalConverter::ClockPrescaler::SixtyFour);

    ASSERT_THAT(ADCSRA, Eq(createBitMask<uint8_t>(ADPS2, ADPS1)));
}
