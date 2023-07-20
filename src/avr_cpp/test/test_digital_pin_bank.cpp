#include <stdint.h>

#include <gmock/gmock.h>

#include <avr_cpp/digital_pin_bank.h>

using namespace ::testing;
using namespace avr_cpp;

constexpr uint8_t NOT_RELEVANT = 0;
constexpr uint8_t ALL_INPUT_PINS = 0;
constexpr uint8_t ALL_OUTPUT_PINS = ~0;
constexpr uint8_t ALL_PINS_LOW = 0;
constexpr uint8_t ALL_PINS_HIGH = ~0;

TEST(DigitalPinBankCreation, DoesNotChangePinModes) {
    uint8_t pinModes = 0xA3;
    uint8_t pins = NOT_RELEVANT;

    DigitalPinBank<> pinBank(pinModes, pins);

    ASSERT_THAT(pinModes, Eq(0xA3));
}

TEST(DigitalPinBankCreation, DoesNotChangePinValues) {
    uint8_t pinModes = NOT_RELEVANT;
    uint8_t pins = 0xF9;

    DigitalPinBank<> pinBank(pinModes, pins);

    ASSERT_THAT(pins, Eq(0xF9));
}

class ConfigureInputPins : public Test {
public:
    ConfigureInputPins() :
        pinModes(ALL_OUTPUT_PINS), pins(NOT_RELEVANT),
        pinBank(pinModes, pins) {}

    uint8_t pinModes;
    uint8_t pins;
    DigitalPinBank<> pinBank;
};

TEST_F(ConfigureInputPins, UnsetsPinModeBits) {
    pinBank.configureInputPins(4, 0, 5);

    ASSERT_THAT(pinModes, Eq(0b1100'1110));
}

TEST_F(ConfigureInputPins, IgnoresOutOfRangePinConfigurations) {
    constexpr auto LOW_OUT_OF_RANGE_PIN = -1;
    constexpr auto HIGH_OUT_OF_RANGE_PIN = 8;

    pinBank.configureInputPins(LOW_OUT_OF_RANGE_PIN,
                               HIGH_OUT_OF_RANGE_PIN,
                               6, 1, 0);

    ASSERT_THAT(pinModes, Eq(0b1011'1100));
}

class ConfigureOutputPins : public Test {
public:
    ConfigureOutputPins() :
        pinModes(ALL_INPUT_PINS), pins(NOT_RELEVANT),
        pinBank(pinModes, pins) {}

    uint8_t pinModes;
    uint8_t pins;
    DigitalPinBank<> pinBank;
};

TEST_F(ConfigureOutputPins, SetsPinModeBits) {
    pinBank.configureOutputPins(3, 1, 7);

    ASSERT_THAT(pinModes, Eq(0b1000'1010));
}

TEST_F(ConfigureOutputPins, IgnoresOutOfRangePinConfigurations) {
    constexpr auto LOW_OUT_OF_RANGE_PIN = -4;
    constexpr auto HIGH_OUT_OF_RANGE_PIN = 10;

    pinBank.configureOutputPins(HIGH_OUT_OF_RANGE_PIN, 
                                3, 4,
                                LOW_OUT_OF_RANGE_PIN);

    ASSERT_THAT(pinModes, Eq(0b0001'1000));
}

class ReadPin : public Test {
public:
    ReadPin() : 
        pinModes(NOT_RELEVANT), pins(NOT_RELEVANT),
        pinBank(pinModes, pins) {

        constexpr auto NUM_PINS = 8;
        for (auto pin = 0; pin < NUM_PINS; ++pin) {
            pinBank.configureInputPins(pin);
        }
    }

    uint8_t pinModes;
    uint8_t pins;
    DigitalPinBank<> pinBank;
};

TEST_F(ReadPin, ReturnsFalseUponReadingLowInput) {
    ASSERT_FALSE(pinBank.readPin(7));
}

TEST_F(ReadPin, ReturnsTrueUponReadingHighInput) {
    pins = ALL_PINS_HIGH;

    ASSERT_TRUE(pinBank.readPin(4));
}

TEST_F(ReadPin, ReturnsFalseUponReadingOutOfRangePin) {
    pins = ALL_PINS_HIGH;

    ASSERT_FALSE(pinBank.readPin(8));
}

TEST_F(ReadPin, ReturnsFalseUponReadingOutputPins) {
    pinBank.configureOutputPins(0);
    pins = ALL_PINS_HIGH;

    ASSERT_FALSE(pinBank.readPin(0));
}

class WritePin : public Test {
public:
    WritePin() : 
        pinModes(NOT_RELEVANT), pins(NOT_RELEVANT),
        pinBank(pinModes, pins) {

        constexpr auto NUM_PINS = 8;
        for (auto pin = 0; pin < NUM_PINS; ++pin) {
            pinBank.configureOutputPins(pin);
        }
    }

    uint8_t pinModes;
    uint8_t pins;
    DigitalPinBank<> pinBank;
};

TEST_F(WritePin, WritesHighToOneOutputPin) {
    pins = ALL_PINS_LOW;

    pinBank.writePin(2, true);

    ASSERT_THAT(pins, Eq(0x04));
}

TEST_F(WritePin, WritesLowToOneOutputPin) {
    pins = ALL_PINS_HIGH;

    pinBank.writePin(6, false);

    ASSERT_THAT(pins, Eq(0b1011'1111));
}

TEST_F(WritePin, WritesToMultipleOutputPins) {
    pins = ALL_PINS_LOW;

    pinBank.writePin(2, true);
    pinBank.writePin(3, true);

    ASSERT_THAT(pins, Eq(0x0C));
}

TEST_F(WritePin, IgnoresWritesToOutOfRangePins) {
    pins = ALL_PINS_LOW;

    pinBank.writePin(8, true);

    ASSERT_THAT(pins, Eq(ALL_PINS_LOW));
}

TEST_F(WritePin, IgnoresWritesToInputPins) {
    pinBank.configureInputPins(6);
    pins = ALL_PINS_LOW;

    pinBank.writePin(6, true);

    ASSERT_THAT(pins, Eq(ALL_PINS_LOW));
}
