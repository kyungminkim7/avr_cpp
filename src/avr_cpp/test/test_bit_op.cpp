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

TEST(CreateBitMask, SetsOneBit) {
    ASSERT_THAT(createBitMask<uint8_t>(6), Eq(0b0100'0000));
}

TEST(CreateBitMask, SetsMultipleBits) {
    ASSERT_THAT(createBitMask<uint8_t>(2, 7), Eq(0b1000'0100));
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
    setBits(value, 1, 2, 4);

    ASSERT_THAT(value, Eq(0b0001'0110));
}

TEST_F(SetBits, SetsMultipleBitsOfAnyOrder) {
    setBits(value, 3, 1, 7);

    ASSERT_THAT(value, Eq(0b1000'1010));
}

class SetBitsInRange : public Test {
public:
    uint8_t value = NO_BITS_SET;
};

TEST_F(SetBitsInRange, SetsMultipleBits) {
    setBitsInRange(value, 5, 0, 3);

    ASSERT_THAT(value, Eq(0b0010'1001));
}

TEST_F(SetBitsInRange, IgnoresOutOfRangeBits) {
    setBitsInRange(value, -1, 8);

    ASSERT_THAT(value, Eq(NO_BITS_SET));
}

TEST_F(SetBitsInRange, SetsInRangeBitsAndIgnoresOutOfRangeBits) {
    constexpr auto LOW_OUT_OF_RANGE_BIT = -4;
    constexpr auto HIGH_OUT_OF_RANGE_BIT = -4;

    setBitsInRange(value, 
        HIGH_OUT_OF_RANGE_BIT,
        4, 1, 7,
        LOW_OUT_OF_RANGE_BIT);

    ASSERT_THAT(value, Eq(0b1001'0010));
}

class UnsetBits: public Test {
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
    unsetBits(value, 0, 3, 7);

    ASSERT_THAT(value, Eq(0b0111'0110));
}

TEST_F(UnsetBits, UnsetsMultipleBitsOfAnyOrder) {
    unsetBits(value, 7, 3, 0);

    ASSERT_THAT(value, Eq(0b0111'0110));
}

class UnsetBitsInRange : public Test {
public:
    uint8_t value = ALL_BITS_SET;
};

TEST_F(UnsetBitsInRange, UnsetsMultipleBits) {
    unsetBitsInRange(value, 1, 3, 7);

    ASSERT_THAT(value, Eq(0b0111'0101));
}

TEST_F(UnsetBitsInRange, IgnoresOutOfRangeBits) {
    unsetBitsInRange(value, -1, 10);

    ASSERT_THAT(value, Eq(ALL_BITS_SET));
}

TEST_F(UnsetBitsInRange, UnsetsInRangeBitsAndIgnoresOutOfRangeBits) {
    constexpr auto LOW_OUT_OF_RANGE_BIT = -4;
    constexpr auto HIGH_OUT_OF_RANGE_BIT = -4;

    unsetBitsInRange(value, 
        HIGH_OUT_OF_RANGE_BIT,
        4, 1, 7,
        LOW_OUT_OF_RANGE_BIT);

    ASSERT_THAT(value, Eq(0b0110'1101));
}

TEST(GetBit, ReturnsFalseForLowBitValue) {
    uint8_t value = NO_BITS_SET;

    ASSERT_FALSE(getBit(value, 4));
}

TEST(GetBit, ReturnsTrueForHighBitValue) {
    uint8_t value = ALL_BITS_SET;

    ASSERT_TRUE(getBit(value, 4));
}

TEST(AreAllBitsSetWithNoBitArguments, ReturnsFalseIfNoBitsAreSet) {
    uint8_t value = NO_BITS_SET;

    ASSERT_FALSE(areAllBitsSet(value));
}

TEST(AreAllBitsSetWithNoBitArguments, ReturnsTrueIfAllBitsAreSet) {
    uint8_t value = ALL_BITS_SET;

    ASSERT_TRUE(areAllBitsSet(value));
}

TEST(AreAllBitsSetWithNoBitArguments, ReturnsFalseIfSomeButNotAllBitsAreSet) {
    uint8_t value = 0xAA;

    ASSERT_FALSE(areAllBitsSet(value));
}

TEST(AreAllBitsSetWithOneBitArgument, ReturnsFalseIfBitIsNotSet) {
    uint8_t value = ALL_BITS_SET;
    unsetBits(value, 1);

    ASSERT_FALSE(areAllBitsSet(value, 1));
}

TEST(AreAllBitsSetWithOneBitArgument, ReturnsTrueIfBitIsSet) {
    uint8_t value = NO_BITS_SET;
    setBits(value, 2);

    ASSERT_TRUE(areAllBitsSet(value, 2));
}

TEST(AreAllBitsSetWithMultipleBitArguments, ReturnsFalseIfNoSpecifiedBitsAreSet) {
    uint8_t value = ALL_BITS_SET;
    unsetBits(value, 2, 3);

    ASSERT_FALSE(areAllBitsSet(value, 2, 3));
}

TEST(AreAllBitsSetWithMultipleBitArguments, ReturnsTrueIfAllSpecifiedBitsAreSet) {
    uint8_t value = NO_BITS_SET;
    setBits(value, 1, 5, 6);

    ASSERT_TRUE(areAllBitsSet(value, 5, 6));
}

TEST(AreAllBitsSetWithMultipleBitArguments, ReturnsFalseIfSomeButNotAllSpecifiedBitsAreSet) {
    uint8_t value = NO_BITS_SET;
    setBits(value, 7);

    ASSERT_FALSE(areAllBitsSet(value, 1, 7));
}

TEST(AreAllBitsUnsetWithNoBitArguments, ReturnsFalseIfAllBitsAreSet) {
    uint8_t value = ALL_BITS_SET;

    ASSERT_FALSE(areAllBitsUnset(value));
}

TEST(AreAllBitsUnsetWithNoBitArguments, ReturnsTrueIfAllBitsAreUnset) {
    uint8_t value = NO_BITS_SET;

    ASSERT_TRUE(areAllBitsUnset(value));
}

TEST(AreAllBitsUnsetWithNoBitArguments, ReturnsFalseIfSomeButNotAllBitsAreUnset) {
    uint8_t value = 0xAA;

    ASSERT_FALSE(areAllBitsUnset(value));
}

TEST(AreAllBitsUnsetWithOneBitArgument, ReturnsFalseIfBitIsSet) {
    uint8_t value = NO_BITS_SET;
    setBits(value, 1);

    ASSERT_FALSE(areAllBitsUnset(value, 1));
}

TEST(AreAllBitsUnsetWithOneBitArgument, ReturnsTrueIfBitIsUnset) {
    uint8_t value = ALL_BITS_SET;
    unsetBits(value, 2);

    ASSERT_TRUE(areAllBitsUnset(value, 2));
}

TEST(AreAllBitsUnsetWithMultipleBitArguments, ReturnsFalseIfAllSpecifiedBitsAreSet) {
    uint8_t value = NO_BITS_SET;
    setBits(value, 2, 3);

    ASSERT_FALSE(areAllBitsUnset(value, 2, 3));
}

TEST(AreAllBitsUnsetWithMultipleBitArguments, ReturnsTrueIfAllSpecifiedBitsAreUnset) {
    uint8_t value = ALL_BITS_SET;
    unsetBits(value, 1, 5, 6);

    ASSERT_TRUE(areAllBitsUnset(value, 5, 6));
}

TEST(AreAllBitsUnsetWithMultipleBitArguments, ReturnsFalseIfSomeButNotAllSpecifiedBitsAreUnset) {
    uint8_t value = ALL_BITS_SET;
    unsetBits(value, 1);

    ASSERT_FALSE(areAllBitsSet(value, 1, 7));
}