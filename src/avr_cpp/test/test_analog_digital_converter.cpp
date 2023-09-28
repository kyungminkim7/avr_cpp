#include <gmock/gmock.h>

#include <avr/io.h>

#include <avr_cpp/analog_digital_converter.h>
#include <avr_cpp/bit.h>
#include <avr_cpp/matchers.h>

using namespace ::testing;
using namespace avr_cpp;

class SetVoltageReference : public Test {
public:
    static constexpr auto CLOCK_PRESCALER = AnalogDigitalConverter::ClockPrescaler::Two;
    static constexpr auto TRIGGER_MODE = AnalogDigitalConverter::TriggerMode::Single;

    void SetUp() override {
        ADMUX = 0;
    }
};

TEST_F(SetVoltageReference, AREF) {
    ADMUX = 0xFF;

    AnalogDigitalConverter adc(AnalogDigitalConverter::VoltageReference::AREF,
                               CLOCK_PRESCALER, TRIGGER_MODE);

    ASSERT_THAT(ADMUX, BitsAreUnset(REFS1, REFS0));
}

TEST_F(SetVoltageReference, AVCC) {
    AnalogDigitalConverter adc(AnalogDigitalConverter::VoltageReference::AVCC,
                               CLOCK_PRESCALER, TRIGGER_MODE);

    ASSERT_THAT(ADMUX, Eq(createBitMask<uint8_t>(REFS0)));
}

TEST_F(SetVoltageReference, Internal1_1V) {
    AnalogDigitalConverter adc(AnalogDigitalConverter::VoltageReference::Internal1_1V,
                               CLOCK_PRESCALER, TRIGGER_MODE);

    ASSERT_THAT(ADMUX, Eq(createBitMask<uint8_t>(REFS1, REFS0)));
}

class SetClockPrescaler : public Test {
public:
    static constexpr auto VOLTAGE_REFERENCE = AnalogDigitalConverter::VoltageReference::AVCC;
    static constexpr auto TRIGGER_MODE = AnalogDigitalConverter::TriggerMode::Single;

    void SetUp() override {
        ADCSRA = 0;
    }
};

TEST_F(SetClockPrescaler, Two) {
    ADCSRA = 0xFF;

    AnalogDigitalConverter adc(VOLTAGE_REFERENCE,
                               AnalogDigitalConverter::ClockPrescaler::Two,
                               TRIGGER_MODE);

    ASSERT_THAT(ADCSRA, BitsAreUnset(ADPS2, ADPS1, ADPS0));
}

TEST_F(SetClockPrescaler, Four) {
    AnalogDigitalConverter adc(VOLTAGE_REFERENCE,
                               AnalogDigitalConverter::ClockPrescaler::Four,
                               TRIGGER_MODE);

    ASSERT_THAT(ADCSRA, BitsAreSet(ADPS1));
    ASSERT_THAT(ADCSRA, BitsAreUnset(ADPS2, ADPS0));
}

TEST_F(SetClockPrescaler, Eight) {
    AnalogDigitalConverter adc(VOLTAGE_REFERENCE,
                               AnalogDigitalConverter::ClockPrescaler::Eight,
                               TRIGGER_MODE);

    ASSERT_THAT(ADCSRA, BitsAreSet(ADPS1, ADPS0));
    ASSERT_THAT(ADCSRA, BitsAreUnset(ADPS2));
}

TEST_F(SetClockPrescaler, Sixteen) {
    AnalogDigitalConverter adc(VOLTAGE_REFERENCE,
                               AnalogDigitalConverter::ClockPrescaler::Sixteen,
                               TRIGGER_MODE);

    ASSERT_THAT(ADCSRA, BitsAreSet(ADPS2));
    ASSERT_THAT(ADCSRA, BitsAreUnset(ADPS1, ADPS0));
}

TEST_F(SetClockPrescaler, ThirtyTwo) {
    AnalogDigitalConverter adc(VOLTAGE_REFERENCE,
                               AnalogDigitalConverter::ClockPrescaler::ThirtyTwo,
                               TRIGGER_MODE);

    ASSERT_THAT(ADCSRA, BitsAreSet(ADPS2, ADPS0));
    ASSERT_THAT(ADCSRA, BitsAreUnset(ADPS1));
}

TEST_F(SetClockPrescaler, SixtyFour) {
    AnalogDigitalConverter adc(VOLTAGE_REFERENCE,
                               AnalogDigitalConverter::ClockPrescaler::SixtyFour,
                               TRIGGER_MODE);

    ASSERT_THAT(ADCSRA, BitsAreSet(ADPS2, ADPS1));
    ASSERT_THAT(ADCSRA, BitsAreUnset(ADPS0));
}

TEST_F(SetClockPrescaler, OneHundredTwentyEight) {
    AnalogDigitalConverter adc(VOLTAGE_REFERENCE,
                               AnalogDigitalConverter::ClockPrescaler::OneHundredTwentyEight,
                               TRIGGER_MODE);

    ASSERT_THAT(ADCSRA, BitsAreSet(ADPS2, ADPS1, ADPS0));
}

TEST(Creation, EnablesADC) {
    AnalogDigitalConverter adc(AnalogDigitalConverter::VoltageReference::AVCC, 
                               AnalogDigitalConverter::ClockPrescaler::Eight, 
                               AnalogDigitalConverter::TriggerMode::Single);

    ASSERT_THAT(ADCSRA, BitsAreSet(ADEN));
}

TEST(Destruction, DisablesADC) {
    {
        AnalogDigitalConverter adc(AnalogDigitalConverter::VoltageReference::AVCC, 
                                   AnalogDigitalConverter::ClockPrescaler::Eight, 
                                   AnalogDigitalConverter::TriggerMode::Single);
    }

    ASSERT_THAT(ADCSRA, BitsAreUnset(ADEN));
}

TEST(StartConversion, SetsADSCBit) {
    AnalogDigitalConverter adc(AnalogDigitalConverter::VoltageReference::AVCC, 
                               AnalogDigitalConverter::ClockPrescaler::Eight, 
                               AnalogDigitalConverter::TriggerMode::Single);

    adc.startConversion();

    ASSERT_THAT(ADCSRA, BitsAreSet(ADSC));
}

class IsConversionInProgress : public Test {

public:
    IsConversionInProgress() : adc(AnalogDigitalConverter::VoltageReference::Internal1_1V, 
                                   AnalogDigitalConverter::ClockPrescaler::SixtyFour, 
                                   AnalogDigitalConverter::TriggerMode::Single) {
        adc.startConversion();
    }

    AnalogDigitalConverter adc;
};

TEST_F(IsConversionInProgress, ReturnsTrueIfADSCBitIsSet) {
    ASSERT_TRUE(adc.isConversionInProgress());
}

TEST_F(IsConversionInProgress, ReturnsFalseIfADSCBitIsCleared) {
    unsetBits(ADCSRA, ADSC);
    ASSERT_FALSE(adc.isConversionInProgress());
}

class SetTriggerMode : public Test {
public:
    static constexpr auto VOLTAGE_REFERENCE = AnalogDigitalConverter::VoltageReference::Internal1_1V;
    static constexpr auto CLOCK_PRESCALER = AnalogDigitalConverter::ClockPrescaler::SixtyFour;
};

TEST_F(SetTriggerMode, ClearsADATEBitUponDisable) {
    setBits(ADCSRA, ADATE);

    AnalogDigitalConverter adc{VOLTAGE_REFERENCE, CLOCK_PRESCALER,
                               AnalogDigitalConverter::TriggerMode::Single};

    ASSERT_THAT(ADCSRA, BitsAreUnset(ADATE));
}

TEST_F(SetTriggerMode, AutoSetsADATEBit) {
    AnalogDigitalConverter adc{VOLTAGE_REFERENCE, CLOCK_PRESCALER,
                               AnalogDigitalConverter::TriggerMode::Auto};

    ASSERT_THAT(ADCSRA, BitsAreSet(ADATE));
}

class GetResult: public Test {
public:
    GetResult() : adc(AnalogDigitalConverter::VoltageReference::Internal1_1V,
                      AnalogDigitalConverter::ClockPrescaler::SixtyFour,
                      AnalogDigitalConverter::TriggerMode::Auto) {
        adc.startConversion();
        ADC = 0x3A4D;
    }

    AnalogDigitalConverter adc;
};

TEST_F(GetResult, ReturnsADC) {
    ASSERT_THAT(adc.getResult(), Eq(0x3A4D));
}

TEST_F(GetResult, HighByte) {
    ASSERT_THAT(adc.getResultHighByte(), Eq(0x3A));
}

TEST_F(GetResult, LowByte) {
    ASSERT_THAT(adc.getResultLowByte(), Eq(0x4D));
}

class AdjustResult : public Test {
public:
    static constexpr auto VOLTAGE_REFERENCE = AnalogDigitalConverter::VoltageReference::Internal1_1V;
    static constexpr auto CLOCK_PRESCALER = AnalogDigitalConverter::ClockPrescaler::Two;
    static constexpr auto TRIGGER_MODE = AnalogDigitalConverter::TriggerMode::Single;
};

TEST_F(AdjustResult, Right) {
    setBits(ADMUX, ADLAR);

    AnalogDigitalConverter(VOLTAGE_REFERENCE,
                           CLOCK_PRESCALER,
                           TRIGGER_MODE,
                           AnalogDigitalConverter::AdjustResult::Right);

    ASSERT_THAT(ADMUX, BitsAreUnset(ADLAR));
}

TEST_F(AdjustResult, Left) {
    unsetBits(ADMUX, ADLAR);

    AnalogDigitalConverter(VOLTAGE_REFERENCE,
                           CLOCK_PRESCALER,
                           TRIGGER_MODE,
                           AnalogDigitalConverter::AdjustResult::Left);

    ASSERT_THAT(ADMUX, BitsAreSet(ADLAR));
}

class SetChannel : public Test {
public:
    SetChannel() : adc(AnalogDigitalConverter::VoltageReference::Internal1_1V, 
                       AnalogDigitalConverter::ClockPrescaler::SixtyFour, 
                       AnalogDigitalConverter::TriggerMode::Single) { 
        ADMUX &= 0xf0;
    }

    AnalogDigitalConverter adc;
};

TEST_F(SetChannel, SetsMUXBits) {
    adc.setChannel(3);

    ASSERT_THAT(ADMUX & 0x0f, Eq(3));
}

TEST_F(SetChannel, DoesNotModifyNonMUXBits) {
    ADMUX = 0xa0;

    adc.setChannel(3);

    ASSERT_THAT(ADMUX & 0xf0, Eq(0xa0));
}

TEST_F(SetChannel, ClearsMUXBits) {
    adc.setChannel(3);

    adc.setChannel(0);

    ASSERT_THAT(ADMUX & 0x0f, Eq(0));
}