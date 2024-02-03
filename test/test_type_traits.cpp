#include <gmock/gmock.h>

#include <avr_cpp/type_traits.h>

using namespace ::testing;
using namespace avr_cpp;

TEST(TestSign, ReturnsOneForPositiveNumbers) {
    ASSERT_THAT(Sign<50>::value, Eq(1));
}

TEST(TestSign, ReturnsMinusOneForNegativeNumbers) {
    ASSERT_THAT(Sign<-23>::value, Eq(-1));
}

TEST(TestAbsoluteValue, PositiveNumbers) {
    ASSERT_THAT(AbsoluteValue<40>::value, Eq(40));
}

TEST(TestAbsoluteValue, NegativeNumbers) {
    ASSERT_THAT(AbsoluteValue<-38>::value, Eq(38));
}

TEST(TestGreatestCommonDivisor, ReturnsGCD) {
    const auto result = GreatestCommonDivisor<30, 20>::value;
    ASSERT_THAT(result, Eq(10));
}

enum class ScopedEnumUint8 : uint8_t {};

TEST(TestUnderlyingType, ReturnsScopedEnumUnderlyingType) {
    const auto result = std::is_same_v<
        uint8_t, 
        UnderlyingType<ScopedEnumUint8>
    >;
    ASSERT_TRUE(result);
}