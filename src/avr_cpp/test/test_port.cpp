#include <stdint.h>

#include <gmock/gmock.h>

#include <avr/io.h>

#include <avr_cpp/matchers.h>
#include <avr_cpp/port.h>

using namespace ::testing;
using namespace avr_cpp;

constexpr uint8_t NOT_RELEVANT = 0;
constexpr uint8_t ALL_INPUT_PINS = 0;
constexpr uint8_t ALL_OUTPUT_PINS = ~0;
constexpr uint8_t ALL_PINS_LOW = 0;
constexpr uint8_t ALL_PINS_HIGH = ~0;

TEST(PortCreation, DoesNotChangeDataDirectionValues) {
    DDRB = 0xA3;

    makePort(DDRB, PINB, PORTB);

    ASSERT_THAT(DDRB, Eq(0xA3));
}

TEST(PortCreation, DoesNotChangeInputPinValues) {
    PINB = 0xF9;

    makePort(DDRB, PINB, PORTB);

    ASSERT_THAT(PINB, Eq(0xF9));
}

TEST(PortCreation, DoesNotChangeOutputPinValues) {
    PORTB = 0xE2;

    makePort(DDRB, PINB, PORTB);

    ASSERT_THAT(PORTB, Eq(0xE2));
}

class ConfigureInputPins : public Test {
public:
    ConfigureInputPins() : port(DDRB, PINB, PORTB) {}

    void SetUp() override {
        DDRB = ALL_OUTPUT_PINS;
    }

    Port<uint8_t> port;
};

TEST_F(ConfigureInputPins, UnsetsOneDataDirectionBit) {
    port.configureInputPins(DDB3);

    ASSERT_THAT(DDRB, BitsAreUnset(DDB3));
}

TEST_F(ConfigureInputPins, UnsetsMultipleDataDirectionBits) {
    port.configureInputPins(DDB0, DDB4, DDB5);

    ASSERT_THAT(DDRB, BitsAreUnset(DDB0, DDB4, DDB5));
}

TEST_F(ConfigureInputPins, UnsetsMultipleDataDirectionBitsOfAnyOrder) {
    port.configureInputPins(DDB3, DDB2, DDB5);

    ASSERT_THAT(DDRB, BitsAreUnset(DDB3, DDB2, DDB5));
}

class ConfigureOutputPins : public Test {
public:
    ConfigureOutputPins() : port(DDRB, PINB, PORTB) {}

    void SetUp() override {
        DDRB = ALL_INPUT_PINS;
    }

    Port<uint8_t> port;
};

TEST_F(ConfigureOutputPins, SetsOneDataDirectionBit) {
    port.configureOutputPins(DDB0);

    ASSERT_THAT(DDRB, BitsAreSet(DDB0));
}

TEST_F(ConfigureOutputPins, SetsMultipleDataDirectionBits) {
    port.configureOutputPins(DDB3, DDB1, DDB7);

    ASSERT_THAT(DDRB, BitsAreSet(DDB1, DDB3, DDB7));
}

TEST_F(ConfigureOutputPins, SetsMultipleDataDirectionBitsOfAnyOrder) {
    port.configureOutputPins(DDB3, DDB2, DDB5);

    ASSERT_THAT(DDRB, BitsAreSet(DDB3, DDB2, DDB5));
}

TEST(ConfigurePins, SetsDataDirectionRegister) {
    DDRB = 0xA7;
    auto port = makePort(DDRB, PINB, PORTB);

    port.configurePins(0x35);

    ASSERT_THAT(DDRB, Eq(0x35));
}

class ReadInputPin : public Test {
public:
    ReadInputPin() : port(DDRB, PINB, PORTB) {
        port.configurePins(ALL_INPUT_PINS);
    }

    Port<uint8_t> port;
};

TEST_F(ReadInputPin, ReturnsFalseUponReadingLowInput) {
    PINB = ALL_PINS_LOW;

    ASSERT_FALSE(port.readInputPin(PINB7));
}

TEST_F(ReadInputPin, ReturnsTrueUponReadingHighInput) {
    PINB = ALL_PINS_HIGH;

    ASSERT_TRUE(port.readInputPin(PINB4));
}

class SetOutputPinsLow : public Test {
public:
    SetOutputPinsLow() : port(DDRB, PINB, PORTB) {
        port.configurePins(ALL_OUTPUT_PINS);
        PORTB = ALL_PINS_HIGH;
    }

    Port<uint8_t> port;
};

TEST_F(SetOutputPinsLow, unsetsOnePin) {
    port.setOutputPinsLow(PB3);

    ASSERT_THAT(PORTB, BitsAreUnset(PB3));
}

TEST_F(SetOutputPinsLow, unsetsMultiplePins) {
    port.setOutputPinsLow(PB1, PB5);

    ASSERT_THAT(PORTB, BitsAreUnset(PB1, PB5));
}

TEST_F(SetOutputPinsLow, unsetsMultiplePinsOfAnyOrder) {
    port.setOutputPinsLow(PB4, PB3, PB6);

    ASSERT_THAT(PORTB, BitsAreUnset(PB4, PB3, PB6));
}

class SetOutputPinsHigh : public Test {
public:
    SetOutputPinsHigh() : port(DDRB, PINB, PORTB) {
        port.configurePins(ALL_OUTPUT_PINS);
        PORTB = ALL_PINS_LOW;
    }

    Port<uint8_t> port;
};

TEST_F(SetOutputPinsHigh, SetsOnePin) {
    port.setOutputPinsHigh(PB2);

    ASSERT_THAT(PORTB, BitsAreSet(PB2));
}

TEST_F(SetOutputPinsHigh, SetsMultiplePins) {
    port.setOutputPinsHigh(PB1, PB2);

    ASSERT_THAT(PORTB, BitsAreSet(PB1, PB2));
}

TEST_F(SetOutputPinsHigh, SetsMultiplePinsOfAnyOrder) {
    port.setOutputPinsHigh(PB4, PB3, PB6);

    ASSERT_THAT(PORTB, BitsAreSet(PB4, PB3, PB6));
}

TEST(SetOutputPins, SetsOutputPins) {
    PORTB = 0x36;

    Port<uint8_t> port(DDRB, PINB, PORTB);
    port.setOutputPins(0x48);

    ASSERT_THAT(PORTB, Eq(0x48));
}

TEST(ToggleOutputPins, FlipsOutputPins) {
    Port<uint8_t> port(DDRB, PINB, PORTB);
    port.setOutputPinsHigh(PB2);
    port.setOutputPinsLow(PB5);

    port.toggleOutputPins(PB2, PB5);

    ASSERT_THAT(PORTB, BitsAreUnset(PB2));
    ASSERT_THAT(PORTB, BitsAreSet(PB5));
}

class EnableInputPinPullupResistors : public Test {
public:
    EnableInputPinPullupResistors() : port(DDRB, PINB, PORTB) {
        PORTB = ALL_PINS_LOW;
        port.configurePins(ALL_INPUT_PINS);
    }

    Port<uint8_t> port;
};

TEST_F(EnableInputPinPullupResistors, SetsOneOutputPin) {
    port.enableInputPinPullupResistors(PINB2);

    ASSERT_THAT(PORTB, BitsAreSet(PB2));
}

TEST_F(EnableInputPinPullupResistors, SetsMultipleOutputPins) {
    port.enableInputPinPullupResistors(PINB3, PINB4, PINB5);

    ASSERT_THAT(PORTB, BitsAreSet(PB3, PB4, PB5));
}

class DisableInputPinPullupResistors : public Test {
public:
    DisableInputPinPullupResistors() : port(DDRB, PINB, PORTB) {
        PORTB = ALL_PINS_HIGH;
        port.configurePins(ALL_INPUT_PINS);
    }

    Port<uint8_t> port;
};

TEST_F(DisableInputPinPullupResistors, UnsetsOneOutputPin) {
    port.disableInputPinPullupResistors(PINB2);

    ASSERT_THAT(PORTB, BitsAreUnset(PB2));
}

TEST_F(DisableInputPinPullupResistors, UnsetsMultipleOutputPins) {
    port.disableInputPinPullupResistors(PINB3, PINB4, PINB5);

    ASSERT_THAT(PORTB, BitsAreUnset(PB3, PB4, PB5));
}

TEST(SetInputPinPullupResistors, SetOutputPins) {
    PINB = 0xB3;
    auto port = makePort(DDRB, PINB, PORTB);
    port.configurePins(ALL_INPUT_PINS);

    port.setInputPinPullupResistors(0x3C);

    ASSERT_THAT(PORTB, 0x3C);
}