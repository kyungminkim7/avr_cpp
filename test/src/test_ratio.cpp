#include <gmock/gmock.h>

#include <avr_cpp/ratio.h>

using namespace ::testing;
using namespace avr_cpp;

TEST(Ratio, ReducesMembers) {
    using R = Ratio<25, 30>;

    ASSERT_THAT(R::num, Eq(5));
    ASSERT_THAT(R::den, Eq(6));
}

TEST(Ratio, IsRatioReturnsTrue) {
    ASSERT_TRUE(IsRatio<Milli>::value);
}

TEST(Ratio, IsRatioReturnsFalse) {
    ASSERT_FALSE(IsRatio<float>::value);
}

TEST(Ratio, Multiply) {
    using product = Multiply<Ratio<3, 5>,
                             Ratio<7, 8>>;
    ASSERT_THAT(product::num, Eq(3 * 7));
    ASSERT_THAT(product::den, Eq(5 * 8));
}

TEST(Ratio, MultiplyCommonDivisorReducesProduct) {
    using product = Multiply<Ratio<6, 5>,
                             Ratio<3, 8>>;
    ASSERT_THAT(product::num, Eq(9));
    ASSERT_THAT(product::den, Eq(20));
}

TEST(Ratio, Divide) {
    using quotient = Divide<Ratio<3, 5>,
                            Ratio<7, 8>>;
    ASSERT_THAT(quotient::num, Eq(3 * 8));
    ASSERT_THAT(quotient::den, Eq(5 * 7));
}
