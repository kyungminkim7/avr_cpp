#include <gmock/gmock.h>

#include <avr/io.h>

#include <avr_cpp/bit.h>
#include <avr_cpp/chrono.h>
#include <avr_cpp/usart.h>
#include <avr_cpp_test/matchers.h>

using namespace ::testing;
using namespace avr_cpp;

class UsartConstructor : public Test {
public:
    static constexpr auto DATA_SIZE = Usart::DataSize::EightBits;
    static constexpr auto NUM_STOP_BITS = Usart::NumStopBits::One;
    static constexpr auto BAUD_RATE = 9600;

    void SetUp() override {
        UCSR0B = 0;
    }
};

TEST_F(UsartConstructor, EnablesTransmitter) {
    Usart0 usart(DATA_SIZE, NUM_STOP_BITS, BAUD_RATE);

    ASSERT_THAT(UCSR0B, BitsAreSet(TXEN0));
}

TEST_F(UsartConstructor, EnablesReceiver) {
    Usart0 usart(DATA_SIZE, NUM_STOP_BITS, BAUD_RATE);

    ASSERT_THAT(UCSR0B, BitsAreSet(RXEN0));
}

class UsartDestructor : public Test {
public:
    void SetUp() override {
        Usart0 usart(Usart::DataSize::NineBits, 
                     Usart::NumStopBits::Two, 
                     115200ul);
    }
};

TEST_F(UsartDestructor, DisablesTransmitter) {
    ASSERT_THAT(UCSR0B, BitsAreUnset(TXEN0));
}

TEST_F(UsartDestructor, DisablesReceiver) {
    ASSERT_THAT(UCSR0B, BitsAreUnset(RXEN0));
}

class UsartSetNormalSpeedBaudRate : public Test {
public:
    static constexpr auto DATA_SIZE = Usart::DataSize::FiveBits;
    static constexpr auto NUM_STOP_BITS = Usart::NumStopBits::One;

    static constexpr auto BAUD_RATE = 9000ul;
};

TEST_F(UsartSetNormalSpeedBaudRate, setsUsartBaudRateRegister) {
    UBRR0 = 0;

    Usart0 usart(DATA_SIZE, NUM_STOP_BITS, BAUD_RATE);

    ASSERT_THAT(UBRR0, Eq((Chrono::SystemClock::frequency + 8ul * BAUD_RATE) / 
                          (16ul * BAUD_RATE) - 1ul));
}

TEST_F(UsartSetNormalSpeedBaudRate, unsetsDoubleSpeedOperationBit) {
    UCSR0A = 0xFF;

    Usart0 usart(DATA_SIZE, NUM_STOP_BITS, BAUD_RATE);

    ASSERT_THAT(UCSR0A, BitsAreUnset(U2X0));
}

class UsartSetDoubleSpeedBaudRate : public Test {
public:
    static constexpr auto DATA_SIZE = Usart::DataSize::FiveBits;
    static constexpr auto NUM_STOP_BITS = Usart::NumStopBits::One;

    static constexpr auto BAUD_RATE = 9600ul;
};

TEST_F(UsartSetDoubleSpeedBaudRate, setsUsartBaudRateRegister) {
    UBRR0 = 0;

    Usart0 usart(DATA_SIZE, NUM_STOP_BITS, BAUD_RATE);

    ASSERT_THAT(UBRR0, Eq((Chrono::SystemClock::frequency + 4ul * BAUD_RATE) / 
                          (8ul * BAUD_RATE) - 1ul));
}

TEST_F(UsartSetDoubleSpeedBaudRate, setsDoubleSpeedOperationBit) {
    UCSR0A = 0;

    Usart0 usart(DATA_SIZE, NUM_STOP_BITS, BAUD_RATE);

    ASSERT_THAT(UCSR0A, BitsAreSet(U2X0));
}

class UsartSetDataSize : public Test {
public:
    static constexpr auto NUM_STOP_BITS = Usart::NumStopBits::One;
    static constexpr auto BAUD_RATE = 9600ul;
};

TEST_F(UsartSetDataSize, Set5Bits) {
    UCSR0B = 0xFF;
    UCSR0C = 0xFF;

    Usart0 usart(Usart::DataSize::FiveBits, NUM_STOP_BITS, BAUD_RATE);

    ASSERT_THAT(UCSR0B, BitsAreUnset(UCSZ02));
    ASSERT_THAT(UCSR0C, BitsAreUnset(UCSZ01, UCSZ00));
}

TEST_F(UsartSetDataSize, Set6Bits) {
    UCSR0B = 0xFF;
    setBits(UCSR0C, UCSZ01);
    unsetBits(UCSR0C, UCSZ00);

    Usart0 usart(Usart::DataSize::SixBits, NUM_STOP_BITS, BAUD_RATE);

    ASSERT_THAT(UCSR0B, BitsAreUnset(UCSZ02));
    ASSERT_THAT(UCSR0C, BitsAreUnset(UCSZ01));
    ASSERT_THAT(UCSR0C, BitsAreSet(UCSZ00));
}

TEST_F(UsartSetDataSize, Set7Bits) {
    UCSR0B = 0xFF;
    unsetBits(UCSR0C, UCSZ01);
    setBits(UCSR0C, UCSZ00);

    Usart0 usart(Usart::DataSize::SevenBits, NUM_STOP_BITS, BAUD_RATE);

    ASSERT_THAT(UCSR0B, BitsAreUnset(UCSZ02));
    ASSERT_THAT(UCSR0C, BitsAreSet(UCSZ01));
    ASSERT_THAT(UCSR0C, BitsAreUnset(UCSZ00));
}

TEST_F(UsartSetDataSize, Set8Bits) {
    UCSR0B = 0xFF;
    UCSR0C = 0;

    Usart0 usart(Usart::DataSize::EightBits, NUM_STOP_BITS, BAUD_RATE);

    ASSERT_THAT(UCSR0B, BitsAreUnset(UCSZ02));
    ASSERT_THAT(UCSR0C, BitsAreSet(UCSZ01, UCSZ00));
}

TEST_F(UsartSetDataSize, Set9Bits) {
    UCSR0B = 0;
    UCSR0C = 0;

    Usart0 usart(Usart::DataSize::NineBits, NUM_STOP_BITS, BAUD_RATE);

    ASSERT_THAT(UCSR0B, BitsAreSet(UCSZ02));
    ASSERT_THAT(UCSR0C, BitsAreSet(UCSZ01, UCSZ00));
}

class UsartSetNumStopBits : public Test {
public:
    static constexpr auto DATA_SIZE = Usart::DataSize::FiveBits;
    static constexpr auto BAUD_RATE = 9600ul;
};

TEST_F(UsartSetNumStopBits, Sets1Bit) {
    UCSR0C = 0xFF;

    Usart0 usart(DATA_SIZE, Usart::NumStopBits::One, BAUD_RATE);

    ASSERT_THAT(UCSR0C, BitsAreUnset(USBS0));
}

TEST_F(UsartSetNumStopBits, Sets2Bits) {
    UCSR0C = 0;

    Usart0 usart(DATA_SIZE, Usart::NumStopBits::Two, BAUD_RATE);

    ASSERT_THAT(UCSR0C, BitsAreSet(USBS0));
}

class UsartReceiveByte : public Test {
public:
    UsartReceiveByte() : usart(Usart::DataSize::EightBits,
                               Usart::NumStopBits::One, 
                               9600ul) { }

    Usart0 usart;
};

TEST_F(UsartReceiveByte, ReturnsDataUponReceiveComplete) {
    const uint8_t EXPECTED_DATA = 0xAB;

    UDR0 = EXPECTED_DATA;
    setBits(UCSR0A, RXC0); // Signal that buffer contains data

    uint8_t actualData;
    usart >> actualData;

    ASSERT_THAT(actualData, Eq(EXPECTED_DATA));
}

class UsartSendByte: public Test {
public:
    UsartSendByte() : usart(Usart::DataSize::NineBits,
                            Usart::NumStopBits::One,
                            11520ul) { }

    Usart0 usart;
};

TEST_F(UsartSendByte, SendsByteAfterDataRegisterIsEmpty) {
    const uint8_t DATA = 0x35;

    setBits(UCSR0A, UDRE0);

    usart << DATA;

    ASSERT_THAT(UDR0, Eq(DATA));
}
