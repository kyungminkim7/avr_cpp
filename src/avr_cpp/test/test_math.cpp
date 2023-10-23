#include <gmock/gmock.h>

#include <avr_cpp/math.h>

using namespace ::testing;
using namespace avr_cpp;

TEST(Modulo, Integer) {
    ASSERT_THAT(modulo(13, 5), Eq(3));
}

TEST(Modulo, Float) {
    ASSERT_THAT(modulo(13.2f, 5), FloatEq(3.2f));
}