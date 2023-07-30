#include <gmock/gmock.h>

#include <avr/io.h>

#include <avr_cpp/bit_op.h>
#include <avr_cpp/usart0.h>

using namespace ::testing;
using namespace avr_cpp;

class UsartInitialization : public Test {
public:
    static constexpr auto DATA_SIZE = Usart::DataSize::EightBits;
    static constexpr auto NUM_STOP_BITS = Usart::NumStopBits::One;
    static constexpr auto BAUD_RATE = 9600;

    void SetUp() override {
        UCSR0B = 0;
    }
};

TEST_F(UsartInitialization, EnablesTransmitter) {
    Usart0 usart(DATA_SIZE, NUM_STOP_BITS, BAUD_RATE);

    ASSERT_TRUE(areAllBitsSet(UCSR0B, TXEN0));
}

TEST_F(UsartInitialization, EnablesReceiver) {
    Usart0 usart(DATA_SIZE, NUM_STOP_BITS, BAUD_RATE);

    ASSERT_TRUE(areAllBitsSet(UCSR0B, RXEN0));
}

class UsartDestruction : public Test {
public:
    void SetUp() override {
        static constexpr auto DATA_SIZE = Usart::DataSize::NineBits;
        static constexpr auto BAUD_RATE = 115200;
        static constexpr auto NUM_STOP_BITS = Usart::NumStopBits::Two;

        Usart0 usart(DATA_SIZE, NUM_STOP_BITS, BAUD_RATE);
    }
};

TEST_F(UsartDestruction, DisablesTransmitter) {
    ASSERT_TRUE(areAllBitsUnset(UCSR0B, TXEN0));
}

TEST_F(UsartDestruction, DisablesReceiver) {
    ASSERT_TRUE(areAllBitsUnset(UCSR0B, RXEN0));
}

class UsartSetNormalSpeedBaudRate : public Test {
public:
    static constexpr auto DATA_SIZE = Usart::DataSize::FiveBits;
    static constexpr auto NUM_STOP_BITS = Usart::NumStopBits::One;

    static constexpr auto BAUD_RATE = 9000ul;
    static constexpr auto BAUD_TOLERANCE_PERCENT = 2u;
    static constexpr auto SYSTEM_CLOCK_FREQ = 1'000'000ul;
};

TEST_F(UsartSetNormalSpeedBaudRate, setsUsartBaudRateRegister) {
    UBRR0 = 0;

    Usart0 usart(DATA_SIZE, NUM_STOP_BITS, BAUD_RATE, 
                 BAUD_TOLERANCE_PERCENT, SYSTEM_CLOCK_FREQ);

    ASSERT_THAT(UBRR0, Eq((SYSTEM_CLOCK_FREQ + 8ul * BAUD_RATE) / 
                          (16ul * BAUD_RATE) - 1ul));
}

TEST_F(UsartSetNormalSpeedBaudRate, unsetsDoubleSpeedOperationBit) {
    UCSR0A = 0xFF;

    Usart0 usart(DATA_SIZE, NUM_STOP_BITS, BAUD_RATE, 
                 BAUD_TOLERANCE_PERCENT, SYSTEM_CLOCK_FREQ);

    ASSERT_TRUE(areAllBitsUnset(UCSR0A, U2X0));
}

class UsartSetDoubleSpeedBaudRate : public Test {
public:
    static constexpr auto DATA_SIZE = Usart::DataSize::FiveBits;
    static constexpr auto NUM_STOP_BITS = Usart::NumStopBits::One;

    static constexpr auto BAUD_RATE = 9600ul;
    static constexpr auto BAUD_TOLERANCE_PERCENT = 2u;
    static constexpr auto SYSTEM_CLOCK_FREQ = 1'000'000ul;
};

TEST_F(UsartSetDoubleSpeedBaudRate, setsUsartBaudRateRegister) {
    UBRR0 = 0;

    Usart0 usart(DATA_SIZE, NUM_STOP_BITS, BAUD_RATE,
                 BAUD_TOLERANCE_PERCENT, SYSTEM_CLOCK_FREQ);

    ASSERT_THAT(UBRR0, Eq((SYSTEM_CLOCK_FREQ + 4ul * BAUD_RATE) / 
                          (8ul * BAUD_RATE) - 1ul));
}

TEST_F(UsartSetDoubleSpeedBaudRate, setsDoubleSpeedOperationBit) {
    UCSR0A = 0;

    Usart0 usart(DATA_SIZE, NUM_STOP_BITS, BAUD_RATE,
                 BAUD_TOLERANCE_PERCENT, SYSTEM_CLOCK_FREQ);

    ASSERT_TRUE(areAllBitsSet(UCSR0A, U2X0));
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

    ASSERT_TRUE(areAllBitsUnset(UCSR0B, UCSZ02));
    ASSERT_TRUE(areAllBitsUnset(UCSR0C, UCSZ01, UCSZ00));
}

TEST_F(UsartSetDataSize, Set6Bits) {
    UCSR0B = 0xFF;
    setBits(UCSR0C, UCSZ01);
    unsetBits(UCSR0C, UCSZ00);

    Usart0 usart(Usart::DataSize::SixBits, NUM_STOP_BITS, BAUD_RATE);

    ASSERT_TRUE(areAllBitsUnset(UCSR0B, UCSZ02));
    ASSERT_TRUE(areAllBitsUnset(UCSR0C, UCSZ01));
    ASSERT_TRUE(areAllBitsSet(UCSR0C, UCSZ00));
}

TEST_F(UsartSetDataSize, Set7Bits) {
    UCSR0B = 0xFF;
    unsetBits(UCSR0C, UCSZ01);
    setBits(UCSR0C, UCSZ00);

    Usart0 usart(Usart::DataSize::SevenBits, NUM_STOP_BITS, BAUD_RATE);

    ASSERT_TRUE(areAllBitsUnset(UCSR0B, UCSZ02));
    ASSERT_TRUE(areAllBitsSet(UCSR0C, UCSZ01));
    ASSERT_TRUE(areAllBitsUnset(UCSR0C, UCSZ00));
}

TEST_F(UsartSetDataSize, Set8Bits) {
    UCSR0B = 0xFF;
    UCSR0C = 0;

    Usart0 usart(Usart::DataSize::EightBits, NUM_STOP_BITS, BAUD_RATE);

    ASSERT_TRUE(areAllBitsUnset(UCSR0B, UCSZ02));
    ASSERT_TRUE(areAllBitsSet(UCSR0C, UCSZ01, UCSZ00));
}

TEST_F(UsartSetDataSize, Set9Bits) {
    UCSR0B = 0;
    UCSR0C = 0;

    Usart0 usart(Usart::DataSize::NineBits, NUM_STOP_BITS, BAUD_RATE);

    ASSERT_TRUE(areAllBitsSet(UCSR0B, UCSZ02));
    ASSERT_TRUE(areAllBitsSet(UCSR0C, UCSZ01, UCSZ00));
}

class UsartSetNumStopBits : public Test {
public:
    static constexpr auto DATA_SIZE = Usart::DataSize::FiveBits;
    static constexpr auto BAUD_RATE = 9600ul;
};

TEST_F(UsartSetNumStopBits, Sets1Bit) {
    UCSR0C = 0xFF;

    Usart0 usart(DATA_SIZE, Usart::NumStopBits::One, BAUD_RATE);

    ASSERT_TRUE(areAllBitsUnset(UCSR0C, USBS0));
}

TEST_F(UsartSetNumStopBits, Sets2Bits) {
    UCSR0C = 0;

    Usart0 usart(DATA_SIZE, Usart::NumStopBits::Two, BAUD_RATE);

    ASSERT_TRUE(areAllBitsSet(UCSR0C, USBS0));
}

class UsartReceiveByte : public Test {
public:
    static constexpr auto BAUD_RATE = 9600;

    Usart0 usart;

    UsartReceiveByte() : usart(Usart::DataSize::EightBits,
                               Usart::NumStopBits::One, BAUD_RATE) { }
};

TEST_F(UsartReceiveByte, ReturnsDataUponReceiveComplete) {
    const uint8_t DATA = 0xAB;

    UDR0 = DATA;
    setBits(UCSR0A, RXC0);

    ASSERT_THAT(usart.receiveByte(), Eq(DATA));
}

class UsartSendByte : public Test {
public:
    static constexpr auto BAUD_RATE = 11520;

    Usart0 usart;

    UsartSendByte() : usart(Usart::DataSize::NineBits,
                            Usart::NumStopBits::One, BAUD_RATE) { }
};

TEST_F(UsartSendByte, SendsByteAfterDataRegisterIsEmpty) {
    const uint8_t DATA = 0x35;

    setBits(UCSR0A, UDRE0);

    usart.sendByte(DATA);

    ASSERT_THAT(UDR0, Eq(DATA));
}
