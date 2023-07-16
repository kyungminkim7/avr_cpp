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

class SetBits : public Test {
public:
    uint8_t value = NO_BITS_SET;
};

TEST_F(SetBits, SetsOneBit) {
    setBits(value, 3);

    ASSERT_THAT(value, Eq(0b1000));
}

TEST_F(SetBits, DoesNotChangeAlreadySetBits) {
    setBits(value, 4);

    setBits(value, 4);

    ASSERT_THAT(value, Eq(0x10));
}

TEST_F(SetBits, SetsMultipleBits) {
    setBits(value, 5, 0, 3);

    ASSERT_THAT(value, Eq(0b0010'1001));
}

TEST_F(SetBits, IgnoresOutOfRangeBits) {
    setBits(value, -1, 8);

    ASSERT_THAT(value, Eq(NO_BITS_SET));
}

class UnsetBits : public Test {
public:
    uint8_t value = ALL_BITS_SET;
};

TEST_F(UnsetBits, UnsetsOneBit) {
    unsetBits(value, 0);

    ASSERT_THAT(value, Eq(0b1111'1110));
}

TEST_F(UnsetBits, DoesNotChangeAlreadyUnsetBit) {
    unsetBits(value, 5);

    unsetBits(value, 5);

    ASSERT_THAT(value, Eq(0b1101'1111));
}

TEST_F(UnsetBits, UnsetsMultipleBits) {
    unsetBits(value, 7, 1, 3);

    ASSERT_THAT(value, Eq(0b0111'0101));
}

TEST_F(UnsetBits, IgnoresOutOfRangeBits) {
    unsetBits(value, -1, 10);

    ASSERT_THAT(value, Eq(ALL_BITS_SET));
}

TEST(GetBit, ReturnsFalseForLowBitValue) {
    uint8_t value = NO_BITS_SET;

    ASSERT_FALSE(getBit(value, 4));
}

TEST(GetBit, ReturnsTrueForHighBitValue) {
    uint8_t value = ALL_BITS_SET;

    ASSERT_TRUE(getBit(value, 4));
}
