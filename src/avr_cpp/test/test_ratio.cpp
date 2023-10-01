#include <gmock/gmock.h>

#include <etl/ratio.h>

#include <avr_cpp/ratio.h>

using namespace ::testing;
using namespace avr_cpp;

TEST(TestIsRatio, ReturnsTrue) {
    ASSERT_TRUE(IsRatio<etl::milli>::value);
}

TEST(TestIsRatio, ReturnsFalse) {
    ASSERT_FALSE(IsRatio<float>::value);
}

TEST(TestReduce, ReturnsReducedRatio) {
    using reduced = Reduce<etl::ratio<20, 15>>;

    ASSERT_THAT(reduced::num, Eq(20 / 5));
    ASSERT_THAT(reduced::den, Eq(15 / 5));
}

TEST(MultiplyRatiosWithNoCommonDivisor, ReturnsProduct) {
    using product = Multiply<etl::ratio<3, 5>,
                             etl::ratio<7, 8>>;
    ASSERT_THAT(product::num, Eq(3 * 7));
    ASSERT_THAT(product::den, Eq(5 * 8));
}

TEST(MultiplyRatiosWithCommonDivisor, ReturnsReducedProduct) {
    using product = Multiply<etl::ratio<6, 5>,
                             etl::ratio<3, 8>>;
    ASSERT_THAT(product::num, Eq(9));
    ASSERT_THAT(product::den, Eq(20));
}

TEST(DivideRatiosWithNoCommonDivisor, ReturnsQuotient) {
    using quotient = Divide<etl::ratio<3, 5>,
                            etl::ratio<7, 8>>;
    ASSERT_THAT(quotient::num, Eq(3 * 8));
    ASSERT_THAT(quotient::den, Eq(5 * 7));
}
