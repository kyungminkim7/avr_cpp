#include <stdint.h>

#include <gmock/gmock.h>

#include <avr/io.h>

#include <avr_cpp/port.h>
#include <avr_cpp_test/matchers.h>

using namespace ::testing;
using namespace avr_cpp;

namespace {

constexpr uint8_t NOT_RELEVANT = 0;
constexpr uint8_t ALL_INPUT_PINS = 0;
constexpr uint8_t ALL_OUTPUT_PINS = ~0;
constexpr uint8_t ALL_PINS_LOW = 0;
constexpr uint8_t ALL_PINS_HIGH = ~0;

} // namespace

TEST(Port, CreationDoesNotChangeDataDirectionValues) {
    DDRB = 0xA3;

    makePort(DDRB, PINB, PORTB);

    ASSERT_THAT(DDRB, Eq(0xA3));
}

TEST(Port, CreationDoesNotChangeInputPinValues) {
    PINB = 0xF9;

    makePort(DDRB, PINB, PORTB);

    ASSERT_THAT(PINB, Eq(0xF9));
}

TEST(Port, CreationDoesNotChangeOutputPinValues) {
    PORTB = 0xE2;

    makePort(DDRB, PINB, PORTB);

    ASSERT_THAT(PORTB, Eq(0xE2));
}

class PortConfigureInputPins : public Test {
public:
    PortConfigureInputPins() : port(DDRB, PINB, PORTB) {}

    void SetUp() override {
        DDRB = ALL_OUTPUT_PINS;
    }

    Port<uint8_t> port;
};

TEST_F(PortConfigureInputPins, UnsetsOneDataDirectionBit) {
    port.configureInputPins(DDB3);

    ASSERT_THAT(DDRB, BitsAreUnset(DDB3));
}

TEST_F(PortConfigureInputPins, UnsetsMultipleDataDirectionBits) {
    port.configureInputPins(DDB0, DDB4, DDB5);

    ASSERT_THAT(DDRB, BitsAreUnset(DDB0, DDB4, DDB5));
}

TEST_F(PortConfigureInputPins, UnsetsMultipleDataDirectionBitsOfAnyOrder) {
    port.configureInputPins(DDB3, DDB2, DDB5);

    ASSERT_THAT(DDRB, BitsAreUnset(DDB3, DDB2, DDB5));
}

class PortConfigureOutputPins : public Test {
public:
    PortConfigureOutputPins() : port(DDRB, PINB, PORTB) {}

    void SetUp() override {
        DDRB = ALL_INPUT_PINS;
    }

    Port<uint8_t> port;
};

TEST_F(PortConfigureOutputPins, SetsOneDataDirectionBit) {
    port.configureOutputPins(DDB0);

    ASSERT_THAT(DDRB, BitsAreSet(DDB0));
}

TEST_F(PortConfigureOutputPins, SetsMultipleDataDirectionBits) {
    port.configureOutputPins(DDB3, DDB1, DDB7);

    ASSERT_THAT(DDRB, BitsAreSet(DDB1, DDB3, DDB7));
}

TEST_F(PortConfigureOutputPins, SetsMultipleDataDirectionBitsOfAnyOrder) {
    port.configureOutputPins(DDB3, DDB2, DDB5);

    ASSERT_THAT(DDRB, BitsAreSet(DDB3, DDB2, DDB5));
}

TEST(Port, ConfigurePinsSetsDataDirectionRegister) {
    DDRB = 0xA7;
    auto port = makePort(DDRB, PINB, PORTB);

    port.configurePins(0x35);

    ASSERT_THAT(DDRB, Eq(0x35));
}

class PortReadInputPin : public Test {
public:
    PortReadInputPin() : port(DDRB, PINB, PORTB) {
        port.configurePins(ALL_INPUT_PINS);
    }

    Port<uint8_t> port;
};

TEST_F(PortReadInputPin, ReturnsFalseUponReadingLowInput) {
    PINB = ALL_PINS_LOW;

    ASSERT_FALSE(port.readInputPin(PINB7));
}

TEST_F(PortReadInputPin, ReturnsTrueUponReadingHighInput) {
    PINB = ALL_PINS_HIGH;

    ASSERT_TRUE(port.readInputPin(PINB4));
}

class PortSetOutputPinsLow : public Test {
public:
    PortSetOutputPinsLow() : port(DDRB, PINB, PORTB) {
        port.configurePins(ALL_OUTPUT_PINS);
        PORTB = ALL_PINS_HIGH;
    }

    Port<uint8_t> port;
};

TEST_F(PortSetOutputPinsLow, unsetsOnePin) {
    port.setOutputPinsLow(PB3);

    ASSERT_THAT(PORTB, BitsAreUnset(PB3));
}

TEST_F(PortSetOutputPinsLow, unsetsMultiplePins) {
    port.setOutputPinsLow(PB1, PB5);

    ASSERT_THAT(PORTB, BitsAreUnset(PB1, PB5));
}

TEST_F(PortSetOutputPinsLow, unsetsMultiplePinsOfAnyOrder) {
    port.setOutputPinsLow(PB4, PB3, PB6);

    ASSERT_THAT(PORTB, BitsAreUnset(PB4, PB3, PB6));
}

class PortSetOutputPinsHigh : public Test {
public:
    PortSetOutputPinsHigh() : port(DDRB, PINB, PORTB) {
        port.configurePins(ALL_OUTPUT_PINS);
        PORTB = ALL_PINS_LOW;
    }

    Port<uint8_t> port;
};

TEST_F(PortSetOutputPinsHigh, SetsOnePin) {
    port.setOutputPinsHigh(PB2);

    ASSERT_THAT(PORTB, BitsAreSet(PB2));
}

TEST_F(PortSetOutputPinsHigh, SetsMultiplePins) {
    port.setOutputPinsHigh(PB1, PB2);

    ASSERT_THAT(PORTB, BitsAreSet(PB1, PB2));
}

TEST_F(PortSetOutputPinsHigh, SetsMultiplePinsOfAnyOrder) {
    port.setOutputPinsHigh(PB4, PB3, PB6);

    ASSERT_THAT(PORTB, BitsAreSet(PB4, PB3, PB6));
}

TEST(Port, SetOutputPins) {
    PORTB = 0x36;

    Port<uint8_t> port(DDRB, PINB, PORTB);
    port.setOutputPins(0x48);

    ASSERT_THAT(PORTB, Eq(0x48));
}

TEST(Port, ToggleOutputPins) {
    Port<uint8_t> port(DDRB, PINB, PORTB);
    port.setOutputPinsHigh(PB2);
    port.setOutputPinsLow(PB5);

    port.toggleOutputPins(PB2, PB5);

    ASSERT_THAT(PORTB, BitsAreUnset(PB2));
    ASSERT_THAT(PORTB, BitsAreSet(PB5));
}

class PortEnableInputPinPullupResistors : public Test {
public:
    PortEnableInputPinPullupResistors() : port(DDRB, PINB, PORTB) {
        PORTB = ALL_PINS_LOW;
        port.configurePins(ALL_INPUT_PINS);
    }

    Port<uint8_t> port;
};

TEST_F(PortEnableInputPinPullupResistors, SetsOneOutputPin) {
    port.enableInputPinPullupResistors(PINB2);

    ASSERT_THAT(PORTB, BitsAreSet(PB2));
}

TEST_F(PortEnableInputPinPullupResistors, SetsMultipleOutputPins) {
    port.enableInputPinPullupResistors(PINB3, PINB4, PINB5);

    ASSERT_THAT(PORTB, BitsAreSet(PB3, PB4, PB5));
}

class PortDisableInputPinPullupResistors : public Test {
public:
    PortDisableInputPinPullupResistors() : port(DDRB, PINB, PORTB) {
        PORTB = ALL_PINS_HIGH;
        port.configurePins(ALL_INPUT_PINS);
    }

    Port<uint8_t> port;
};

TEST_F(PortDisableInputPinPullupResistors, UnsetsOneOutputPin) {
    port.disableInputPinPullupResistors(PINB2);

    ASSERT_THAT(PORTB, BitsAreUnset(PB2));
}

TEST_F(PortDisableInputPinPullupResistors, UnsetsMultipleOutputPins) {
    port.disableInputPinPullupResistors(PINB3, PINB4, PINB5);

    ASSERT_THAT(PORTB, BitsAreUnset(PB3, PB4, PB5));
}

TEST(Port, SetInputPinPullupResistorsSetsOutputPins) {
    PINB = 0xB3;
    auto port = makePort(DDRB, PINB, PORTB);
    port.configurePins(ALL_INPUT_PINS);

    port.setInputPinPullupResistors(0x3C);

    ASSERT_THAT(PORTB, 0x3C);
}
