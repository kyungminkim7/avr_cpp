#include <stdint.h>

#include <gmock/gmock.h>

#include <avr_cpp/digital_port.h>

using namespace ::testing;
using namespace avr_cpp;

constexpr uint8_t NOT_RELEVANT = 0;
constexpr uint8_t ALL_INPUT_PINS = 0;
constexpr uint8_t ALL_OUTPUT_PINS = ~0;
constexpr uint8_t ALL_PINS_LOW = 0;
constexpr uint8_t ALL_PINS_HIGH = ~0;

TEST(PortCreation, DoesNotChangePinModes) {
    uint8_t pinModes = 0xA3;
    uint8_t pins = NOT_RELEVANT;

    DigitalPort<uint8_t>(&pinModes, &pins);

    ASSERT_THAT(pinModes, Eq(0xA3));
}

TEST(PortCreation, DoesNotChangePinValues) {
    uint8_t pinModes = NOT_RELEVANT;
    uint8_t pins = 0xF9;

    DigitalPort<uint8_t>(&pinModes, &pins);

    ASSERT_THAT(pins, Eq(0xF9));
}

class ConfigureInputPins : public Test {
public:
    ConfigureInputPins() :
        pinModes(ALL_OUTPUT_PINS), pins(NOT_RELEVANT),
        port(&pinModes, &pins) {}

    uint8_t pinModes;
    uint8_t pins;
    DigitalPort<uint8_t> port;
};

TEST_F(ConfigureInputPins, UnsetsPinModeBits) {
    port.configureInputPins(4, 0, 5);

    ASSERT_THAT(pinModes, Eq(0b1100'1110));
}

TEST_F(ConfigureInputPins, IgnoresOutOfRangePinConfigurations) {
    constexpr auto LOW_OUT_OF_RANGE_PIN = -1;
    constexpr auto HIGH_OUT_OF_RANGE_PIN = 8;

    port.configureInputPins(LOW_OUT_OF_RANGE_PIN,
                            HIGH_OUT_OF_RANGE_PIN,
                            6, 1, 0);

    ASSERT_THAT(pinModes, Eq(0b1011'1100));
}

class ConfigureOutputPins : public Test {
public:
    ConfigureOutputPins() :
        pinModes(ALL_INPUT_PINS), pins(NOT_RELEVANT),
        port(&pinModes, &pins) {}

    uint8_t pinModes;
    uint8_t pins;
    DigitalPort<uint8_t> port;
};

TEST_F(ConfigureOutputPins, SetsPinModeBits) {
    port.configureOutputPins(3, 1, 7);

    ASSERT_THAT(pinModes, Eq(0b1000'1010));
}

TEST_F(ConfigureOutputPins, IgnoresOutOfRangePinConfigurations) {
    constexpr auto LOW_OUT_OF_RANGE_PIN = -4;
    constexpr auto HIGH_OUT_OF_RANGE_PIN = 10;

    port.configureOutputPins(HIGH_OUT_OF_RANGE_PIN, 
                             3, 4,
                             LOW_OUT_OF_RANGE_PIN);

    ASSERT_THAT(pinModes, Eq(0b0001'1000));
}

class ReadPin : public Test {
public:
    ReadPin() : 
        pinModes(NOT_RELEVANT), pins(NOT_RELEVANT),
        port(&pinModes, &pins) {

        constexpr auto NUM_PINS = 8;
        for (auto pin = 0; pin < NUM_PINS; ++pin) {
            port.configureInputPins(pin);
        }
    }

    uint8_t pinModes;
    uint8_t pins;
    DigitalPort<uint8_t> port;
};

TEST_F(ReadPin, ReturnsFalseUponReadingLowInput) {
    ASSERT_FALSE(port.readPin(7));
}

TEST_F(ReadPin, ReturnsTrueUponReadingHighInput) {
    pins = ALL_PINS_HIGH;

    ASSERT_TRUE(port.readPin(4));
}

TEST_F(ReadPin, ReturnsFalseUponReadingOutOfRangePin) {
    pins = ALL_PINS_HIGH;

    ASSERT_FALSE(port.readPin(8));
}

TEST_F(ReadPin, IgnoresWritesToInputPins) {
    pins = ALL_PINS_LOW;

    port.writePin(6, true);

    ASSERT_THAT(pins, Eq(ALL_PINS_LOW));
}

class PortWithOutputPins : public Test {
public:
    PortWithOutputPins() : 
        pinModes(NOT_RELEVANT), pins(NOT_RELEVANT),
        port(&pinModes, &pins) {

        constexpr auto NUM_PINS = 8;
        for (auto pin = 0; pin < NUM_PINS; ++pin) {
            port.configureOutputPins(pin);
        }
    }

    uint8_t pinModes;
    uint8_t pins;
    DigitalPort<uint8_t> port;
};

TEST_F(PortWithOutputPins, ReturnsFalseUponReadingOutputPins) {
    pins = ALL_PINS_HIGH;

    ASSERT_FALSE(port.readPin(0));
}

TEST_F(PortWithOutputPins, WritesHighToOneOutputPin) {
    pins = ALL_PINS_LOW;

    port.writePin(2, true);

    ASSERT_THAT(pins, Eq(0x04));
}

TEST_F(PortWithOutputPins, WritesLowToOneOutputPin) {
    pins = ALL_PINS_HIGH;

    port.writePin(6, false);

    ASSERT_THAT(pins, Eq(0b1011'1111));
}

TEST_F(PortWithOutputPins, WritesToMultipleOutputPins) {
    pins = ALL_PINS_LOW;

    port.writePin(2, true);
    port.writePin(3, true);

    ASSERT_THAT(pins, Eq(0x0C));
}

TEST_F(PortWithOutputPins, IgnoresWritesToOutOfRangePins) {
    pins = ALL_PINS_LOW;

    port.writePin(8, true);

    ASSERT_THAT(pins, Eq(ALL_PINS_LOW));
}