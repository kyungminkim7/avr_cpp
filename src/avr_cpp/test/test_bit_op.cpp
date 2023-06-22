#include <stdint.h>

#include <gmock/gmock.h>

#include <avr_cpp/bit_op.h>

using namespace ::testing;
using namespace avr_cpp;


constexpr uint8_t NO_BITS_SET = 0;
constexpr uint8_t ALL_BITS_SET = ~NO_BITS_SET;

TEST(IsBitInRange, ReturnsTrueForValidBit) {
    ASSERT_TRUE(isBitInRange<uint16_t>(0));
}

TEST(IsBitInRange, ReturnsFalseForInvalidBit) {
    ASSERT_FALSE(isBitInRange<uint8_t>(-1));
}

TEST(ConvertBitPosition, ReturnsValueWithBitPositionSet) {
    ASSERT_THAT(convertBitPosition<uint8_t>(6), Eq(0b0100'0000));
}

class SetBit : public Test {
public:
    uint8_t value = NO_BITS_SET;
};

TEST_F(SetBit, SetsOneBit) {
    setBit(value, 3);

    ASSERT_THAT(value, Eq(0b1000));
}

TEST_F(SetBit, DoesNotChangeAlreadySetBit) {
    setBit(value, 4);

    setBit(value, 4);

    ASSERT_THAT(value, Eq(0x10));
}

TEST_F(SetBit, SetsMultipleBits) {
    setBit(value, 5);
    setBit(value, 0);

    ASSERT_THAT(value, Eq(0x21));
}

class UnsetBit : public Test {
public:
    uint8_t value = ALL_BITS_SET;
};

TEST_F(UnsetBit, UnsetsOneBit) {
    unsetBit(value, 0);

    ASSERT_THAT(value, Eq(0xFE));
}

TEST_F(UnsetBit, DoesNotChangeAlreadyUnsetBit) {
    unsetBit(value, 5);

    unsetBit(value, 5);

    ASSERT_THAT(value, Eq(0b1101'1111));
}

TEST_F(UnsetBit, UnsetsMultipleBits) {
    unsetBit(value, 7);
    unsetBit(value, 3);

    ASSERT_THAT(value, Eq(0x77));
}

class GetBit : public Test {
public:
    uint8_t value = ALL_BITS_SET;
};

TEST_F(GetBit, ReturnsFalseForLowBitValue) {
    unsetBit(value, 4);

    ASSERT_FALSE(getBit(value, 4));
}

TEST_F(GetBit, ReturnsTrueForHighBitValue) {
    ASSERT_TRUE(getBit(value, 4));
}