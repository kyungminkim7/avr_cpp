#include <gmock/gmock.h>

#include <avr/io.h>

#include <avr_cpp/analog_digital_converter.h>
#include <avr_cpp/bit.h>
#include <avr_cpp_test/matchers.h>

using namespace ::testing;
using namespace avr_cpp;

class ADCSetVoltageReference : public Test {
public:
    static constexpr auto CLOCK_PRESCALER = AnalogDigitalConverter::ClockPrescaler::Two;
    static constexpr auto TRIGGER_MODE = AnalogDigitalConverter::TriggerMode::Single;

    void SetUp() override {
        ADMUX = 0;
    }
};

TEST_F(ADCSetVoltageReference, AREF) {
    ADMUX = 0xFF;

    AnalogDigitalConverter adc(AnalogDigitalConverter::VoltageReference::AREF,
                               CLOCK_PRESCALER, TRIGGER_MODE);

    ASSERT_THAT(ADMUX, BitsAreUnset(REFS1, REFS0));
}

TEST_F(ADCSetVoltageReference, AVCC) {
    AnalogDigitalConverter adc(AnalogDigitalConverter::VoltageReference::AVCC,
                               CLOCK_PRESCALER, TRIGGER_MODE);

    ASSERT_THAT(ADMUX, Eq(createBitMask<uint8_t>(REFS0)));
}

TEST_F(ADCSetVoltageReference, Internal1_1V) {
    AnalogDigitalConverter adc(AnalogDigitalConverter::VoltageReference::Internal1_1V,
                               CLOCK_PRESCALER, TRIGGER_MODE);

    ASSERT_THAT(ADMUX, Eq(createBitMask<uint8_t>(REFS1, REFS0)));
}

class ADCSetClockPrescaler : public Test {
public:
    static constexpr auto VOLTAGE_REFERENCE = AnalogDigitalConverter::VoltageReference::AVCC;
    static constexpr auto TRIGGER_MODE = AnalogDigitalConverter::TriggerMode::Single;

    void SetUp() override {
        ADCSRA = 0;
    }
};

TEST_F(ADCSetClockPrescaler, Two) {
    ADCSRA = 0xFF;

    AnalogDigitalConverter adc(VOLTAGE_REFERENCE,
                               AnalogDigitalConverter::ClockPrescaler::Two,
                               TRIGGER_MODE);

    ASSERT_THAT(ADCSRA, BitsAreUnset(ADPS2, ADPS1, ADPS0));
}

TEST_F(ADCSetClockPrescaler, Four) {
    AnalogDigitalConverter adc(VOLTAGE_REFERENCE,
                               AnalogDigitalConverter::ClockPrescaler::Four,
                               TRIGGER_MODE);

    ASSERT_THAT(ADCSRA, BitsAreSet(ADPS1));
    ASSERT_THAT(ADCSRA, BitsAreUnset(ADPS2, ADPS0));
}

TEST_F(ADCSetClockPrescaler, Eight) {
    AnalogDigitalConverter adc(VOLTAGE_REFERENCE,
                               AnalogDigitalConverter::ClockPrescaler::Eight,
                               TRIGGER_MODE);

    ASSERT_THAT(ADCSRA, BitsAreSet(ADPS1, ADPS0));
    ASSERT_THAT(ADCSRA, BitsAreUnset(ADPS2));
}

TEST_F(ADCSetClockPrescaler, Sixteen) {
    AnalogDigitalConverter adc(VOLTAGE_REFERENCE,
                               AnalogDigitalConverter::ClockPrescaler::Sixteen,
                               TRIGGER_MODE);

    ASSERT_THAT(ADCSRA, BitsAreSet(ADPS2));
    ASSERT_THAT(ADCSRA, BitsAreUnset(ADPS1, ADPS0));
}

TEST_F(ADCSetClockPrescaler, ThirtyTwo) {
    AnalogDigitalConverter adc(VOLTAGE_REFERENCE,
                               AnalogDigitalConverter::ClockPrescaler::ThirtyTwo,
                               TRIGGER_MODE);

    ASSERT_THAT(ADCSRA, BitsAreSet(ADPS2, ADPS0));
    ASSERT_THAT(ADCSRA, BitsAreUnset(ADPS1));
}

TEST_F(ADCSetClockPrescaler, SixtyFour) {
    AnalogDigitalConverter adc(VOLTAGE_REFERENCE,
                               AnalogDigitalConverter::ClockPrescaler::SixtyFour,
                               TRIGGER_MODE);

    ASSERT_THAT(ADCSRA, BitsAreSet(ADPS2, ADPS1));
    ASSERT_THAT(ADCSRA, BitsAreUnset(ADPS0));
}

TEST_F(ADCSetClockPrescaler, OneHundredTwentyEight) {
    AnalogDigitalConverter adc(VOLTAGE_REFERENCE,
                               AnalogDigitalConverter::ClockPrescaler::OneHundredTwentyEight,
                               TRIGGER_MODE);

    ASSERT_THAT(ADCSRA, BitsAreSet(ADPS2, ADPS1, ADPS0));
}

TEST(ADC, CreationEnablesADC) {
    AnalogDigitalConverter adc(AnalogDigitalConverter::VoltageReference::AVCC, 
                               AnalogDigitalConverter::ClockPrescaler::Eight, 
                               AnalogDigitalConverter::TriggerMode::Single);

    ASSERT_THAT(ADCSRA, BitsAreSet(ADEN));
}

TEST(ADC, DestructionDisablesADC) {
    {
        AnalogDigitalConverter adc(AnalogDigitalConverter::VoltageReference::AVCC, 
                                   AnalogDigitalConverter::ClockPrescaler::Eight, 
                                   AnalogDigitalConverter::TriggerMode::Single);
    }

    ASSERT_THAT(ADCSRA, BitsAreUnset(ADEN));
}

TEST(ADC, StartConversionSetsADSCBit) {
    AnalogDigitalConverter adc(AnalogDigitalConverter::VoltageReference::AVCC, 
                               AnalogDigitalConverter::ClockPrescaler::Eight, 
                               AnalogDigitalConverter::TriggerMode::Single);

    adc.startConversion();

    ASSERT_THAT(ADCSRA, BitsAreSet(ADSC));
}

class ADCIsConversionInProgress : public Test {

public:
    ADCIsConversionInProgress() : adc(AnalogDigitalConverter::VoltageReference::Internal1_1V, 
                                      AnalogDigitalConverter::ClockPrescaler::SixtyFour, 
                                      AnalogDigitalConverter::TriggerMode::Single) {
        adc.startConversion();
    }

    AnalogDigitalConverter adc;
};

TEST_F(ADCIsConversionInProgress, ReturnsTrueIfADSCBitIsSet) {
    ASSERT_TRUE(adc.isConversionInProgress());
}

TEST_F(ADCIsConversionInProgress, ReturnsFalseIfADSCBitIsCleared) {
    unsetBits(ADCSRA, ADSC);
    ASSERT_FALSE(adc.isConversionInProgress());
}

class ADCSetTriggerMode : public Test {
public:
    static constexpr auto VOLTAGE_REFERENCE = AnalogDigitalConverter::VoltageReference::Internal1_1V;
    static constexpr auto CLOCK_PRESCALER = AnalogDigitalConverter::ClockPrescaler::SixtyFour;
};

TEST_F(ADCSetTriggerMode, ClearsADATEBitUponDisable) {
    setBits(ADCSRA, ADATE);

    AnalogDigitalConverter adc{VOLTAGE_REFERENCE, CLOCK_PRESCALER,
                               AnalogDigitalConverter::TriggerMode::Single};

    ASSERT_THAT(ADCSRA, BitsAreUnset(ADATE));
}

TEST_F(ADCSetTriggerMode, AutoSetsADATEBit) {
    AnalogDigitalConverter adc{VOLTAGE_REFERENCE, CLOCK_PRESCALER,
                               AnalogDigitalConverter::TriggerMode::Auto};

    ASSERT_THAT(ADCSRA, BitsAreSet(ADATE));
}

class ADCGetResult: public Test {
public:
    ADCGetResult() : adc(AnalogDigitalConverter::VoltageReference::Internal1_1V,
                         AnalogDigitalConverter::ClockPrescaler::SixtyFour,
                         AnalogDigitalConverter::TriggerMode::Auto) {
        adc.startConversion();
        ADC = 0x3A4D;
    }

    AnalogDigitalConverter adc;
};

TEST_F(ADCGetResult, ReturnsADC) {
    ASSERT_THAT(adc.getResult(), Eq(0x3A4D));
}

TEST_F(ADCGetResult, HighByte) {
    ASSERT_THAT(adc.getResultHighByte(), Eq(0x3A));
}

TEST_F(ADCGetResult, LowByte) {
    ASSERT_THAT(adc.getResultLowByte(), Eq(0x4D));
}

class ADCAdjustResult : public Test {
public:
    static constexpr auto VOLTAGE_REFERENCE = AnalogDigitalConverter::VoltageReference::Internal1_1V;
    static constexpr auto CLOCK_PRESCALER = AnalogDigitalConverter::ClockPrescaler::Two;
    static constexpr auto TRIGGER_MODE = AnalogDigitalConverter::TriggerMode::Single;
};

TEST_F(ADCAdjustResult, Right) {
    setBits(ADMUX, ADLAR);

    AnalogDigitalConverter(VOLTAGE_REFERENCE,
                           CLOCK_PRESCALER,
                           TRIGGER_MODE,
                           AnalogDigitalConverter::AdjustResult::Right);

    ASSERT_THAT(ADMUX, BitsAreUnset(ADLAR));
}

TEST_F(ADCAdjustResult, Left) {
    unsetBits(ADMUX, ADLAR);

    AnalogDigitalConverter(VOLTAGE_REFERENCE,
                           CLOCK_PRESCALER,
                           TRIGGER_MODE,
                           AnalogDigitalConverter::AdjustResult::Left);

    ASSERT_THAT(ADMUX, BitsAreSet(ADLAR));
}

class ADCSetChannel : public Test {
public:
    ADCSetChannel() : adc(AnalogDigitalConverter::VoltageReference::Internal1_1V, 
                          AnalogDigitalConverter::ClockPrescaler::SixtyFour, 
                          AnalogDigitalConverter::TriggerMode::Single) { 
        ADMUX &= 0xf0;
    }

    AnalogDigitalConverter adc;
};

TEST_F(ADCSetChannel, SetsMUXBits) {
    adc.setChannel(3);

    ASSERT_THAT(ADMUX & 0x0f, Eq(3));
}

TEST_F(ADCSetChannel, DoesNotModifyNonMUXBits) {
    ADMUX = 0xa0;

    adc.setChannel(3);

    ASSERT_THAT(ADMUX & 0xf0, Eq(0xa0));
}

TEST_F(ADCSetChannel, ClearsMUXBits) {
    adc.setChannel(3);

    adc.setChannel(0);

    ASSERT_THAT(ADMUX & 0x0f, Eq(0));
}