#include <gmock/gmock.h>

#include <avr_cpp/math.h>

using namespace ::testing;
using namespace avr_cpp;

namespace {

TEST(Math, ModuloInteger) {
    ASSERT_THAT(modulo(13, 5), Eq(3));
}

TEST(Math, ModuloFloat) {
    ASSERT_THAT(modulo(13.2f, 5), FloatEq(3.2f));
}

} // namespace
