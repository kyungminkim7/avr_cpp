#include <stdint.h>

#include <gmock/gmock.h>

#include <avr_cpp/bit.h>
#include <avr_cpp_test/matchers.h>

using namespace ::testing;
using namespace avr_cpp;

namespace {

constexpr uint8_t NO_BITS_SET = 0;
constexpr uint8_t ALL_BITS_SET = ~NO_BITS_SET;

} // namespace

TEST(Bit, IsBitInRangeReturnsTrueForValidBit) {
    ASSERT_TRUE(isBitInRange<uint16_t>(0));
}

TEST(Bit, IsBitInRangeReturnsFalseForInvalidBit) {
    ASSERT_FALSE(isBitInRange<uint8_t>(-1));
}

TEST(Bit, CreateBitMaskSetsOneBit) {
    ASSERT_THAT(createBitMask<uint8_t>(6), Eq(0b0100'0000));
}

TEST(Bit, CreateBitMaskSetsMultipleBits) {
    ASSERT_THAT(createBitMask<uint8_t>(2, 7), Eq(0b1000'0100));
}

class BitSet : public Test {
public:
    uint8_t value = NO_BITS_SET;
};

TEST_F(BitSet, OneBit) {
    setBits(value, 3);

    ASSERT_THAT(value, Eq(0b1000));
}

TEST_F(BitSet, DoesNotChangeAlreadySetBits) {
    setBits(value, 4);

    setBits(value, 4);

    ASSERT_THAT(value, Eq(0x10));
}

TEST_F(BitSet, MultipleBits) {
    setBits(value, 1, 2, 4);

    ASSERT_THAT(value, Eq(0b0001'0110));
}

TEST_F(BitSet, MultipleBitsOfAnyOrder) {
    setBits(value, 3, 1, 7);

    ASSERT_THAT(value, Eq(0b1000'1010));
}

class BitSetInRange : public Test {
public:
    uint8_t value = NO_BITS_SET;
};

TEST_F(BitSetInRange, MultipleBits) {
    setBitsInRange(value, 5, 0, 3);

    ASSERT_THAT(value, Eq(0b0010'1001));
}

TEST_F(BitSetInRange, IgnoresOutOfRangeBits) {
    setBitsInRange(value, -1, 8);

    ASSERT_THAT(value, Eq(NO_BITS_SET));
}

TEST_F(BitSetInRange, SetsInRangeBitsAndIgnoresOutOfRangeBits) {
    constexpr auto LOW_OUT_OF_RANGE_BIT = -4;
    constexpr auto HIGH_OUT_OF_RANGE_BIT = -4;

    setBitsInRange(value, 
        HIGH_OUT_OF_RANGE_BIT,
        4, 1, 7,
        LOW_OUT_OF_RANGE_BIT);

    ASSERT_THAT(value, Eq(0b1001'0010));
}

class BitUnset: public Test {
public:
    uint8_t value = ALL_BITS_SET;
};

TEST_F(BitUnset, OneBit) {
    unsetBits(value, 0);

    ASSERT_THAT(value, Eq(0b1111'1110));
}

TEST_F(BitUnset, DoesNotChangeAlreadyUnsetBit) {
    unsetBits(value, 5);

    unsetBits(value, 5);

    ASSERT_THAT(value, Eq(0b1101'1111));
}

TEST_F(BitUnset, UnsetsMultipleBits) {
    unsetBits(value, 0, 3, 7);

    ASSERT_THAT(value, Eq(0b0111'0110));
}

TEST_F(BitUnset, MultipleBitsOfAnyOrder) {
    unsetBits(value, 7, 3, 0);

    ASSERT_THAT(value, Eq(0b0111'0110));
}

class BitUnsetInRange : public Test {
public:
    uint8_t value = ALL_BITS_SET;
};

TEST_F(BitUnsetInRange, MultipleBits) {
    unsetBitsInRange(value, 1, 3, 7);

    ASSERT_THAT(value, Eq(0b0111'0101));
}

TEST_F(BitUnsetInRange, IgnoresOutOfRangeBits) {
    unsetBitsInRange(value, -1, 10);

    ASSERT_THAT(value, Eq(ALL_BITS_SET));
}

TEST_F(BitUnsetInRange, UnsetsInRangeBitsAndIgnoresOutOfRangeBits) {
    constexpr auto LOW_OUT_OF_RANGE_BIT = -4;
    constexpr auto HIGH_OUT_OF_RANGE_BIT = -4;

    unsetBitsInRange(value, 
        HIGH_OUT_OF_RANGE_BIT,
        4, 1, 7,
        LOW_OUT_OF_RANGE_BIT);

    ASSERT_THAT(value, Eq(0b0110'1101));
}

TEST(Bit, ToggleBitsFlipsUnsetBit) {
    uint8_t value = 0;

    toggleBits(value, 2);

    ASSERT_THAT(value, 0b0100);
}

TEST(Bit, ToggleBitsFlipsSetBit) {
    uint8_t value = 0xFF;

    toggleBits(value, 3);

    ASSERT_THAT(value, 0b1111'0111);
}

TEST(Bit, ToggleBitsFlipsMultipleBits) {
    uint8_t value = 0;
    setBits(value, 1);
    unsetBits(value, 7);

    toggleBits(value, 1, 7);

    ASSERT_THAT(value, BitsAreUnset(1));
    ASSERT_THAT(value, BitsAreSet(7));
}

TEST(Bit, GetBitReturnsFalseForLowBitValue) {
    uint8_t value = NO_BITS_SET;

    ASSERT_FALSE(getBit(value, 4));
}

TEST(Bit, GetBitReturnsTrueForHighBitValue) {
    uint8_t value = ALL_BITS_SET;

    ASSERT_TRUE(getBit(value, 4));
}
