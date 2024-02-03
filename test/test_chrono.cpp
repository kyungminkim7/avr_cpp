#include <limits>
#include <numeric>
#include <type_traits>

#include <gmock/gmock.h>

#include <avr_cpp/chrono.h>
#include <avr_cpp_test/chrono.h>

using namespace ::testing;
using namespace avr_cpp;
using namespace avr_cpp::Chrono;

TEST(TestDuration, RepType) {
    const auto result = std::is_same_v<typename Duration<float>::rep, 
                                       float>;
    ASSERT_TRUE(result);
}

TEST(TestDuration, PeriodType) {
    const auto result = std::is_same_v<typename Duration<int, Milli>::period, 
                                       Milli>;
    ASSERT_TRUE(result);
}

TEST(TestDuration, ReducesPeriod) {
    using period = Duration<int, Ratio<25, 30>>::period;
    constexpr auto gcd = std::gcd(25, 30);

    ASSERT_THAT(period::num, Eq(25 / gcd));
    ASSERT_THAT(period::den, Eq(30 / gcd));
}

TEST(DefaultConstruction, SetsZeroTickCount) {
    Duration<int> duration;

    ASSERT_THAT(duration.count(), Eq(0));
}

TEST(Construction, SetsTickCount) {
    Duration<float> duration(4.2f);

    ASSERT_THAT(duration.count(), FloatEq(4.2f));
}

TEST(Construction, InvalidConstruction) {
    Duration<float> duration;
}

TEST(TestIsDuration, False) {
    ASSERT_FALSE(IsDuration<float>::value);
}

TEST(TestIsDuration, True) {
    ASSERT_TRUE(IsDuration<Duration<int>>::value);
}

TEST(TestIsHarmonic, ReturnsFalseTypeForNonExactMultiples) {
    const auto result = Duration<int, Ratio<3, 5>>
        ::isHarmonic<Ratio<3, 5 * 2>>
        ::value;

    ASSERT_FALSE(result);
}

TEST(TestIsHarmonic, ReturnsTrueTypeForExactMultiples) {
    const auto result = Duration<int, Ratio<3, 5>>
        ::isHarmonic<Ratio<3 * 7, 5>>
        ::value;
    ASSERT_TRUE(result);
}

TEST(TestDurationCommonType, ReturnsCommonRepType) {
    using commonDuration = etl::common_type_t<Duration<int>, Duration<float>>;

    const auto result = std::is_same_v<commonDuration::rep, 
                                       std::common_type_t<int, float>>;
    ASSERT_TRUE(result);
}

TEST(TestDurationCommonType, ReturnsCommonPeriodType) {
    using commonDuration = etl::common_type_t<Duration<int, Ratio<8, 9>>, 
                                              Duration<int, Ratio<14, 27>>>;

    ASSERT_THAT(commonDuration::period::num, Eq(2));
    ASSERT_THAT(commonDuration::period::den, Eq(27));
}

TEST(DurationCast, CastsRepType) {
    using FromDuration = Duration<int>;
    using ToDuration = Duration<float>;

    constexpr auto duration = durationCast<ToDuration>(FromDuration());
    const auto result = std::is_same_v<decltype(duration)::rep, float>;

    ASSERT_TRUE(result);
}

TEST(DurationCast, CastsPeriodType) {
    using FromDuration = Duration<int>;
    using ToDuration = Duration<int, Milli>;

    constexpr auto duration = durationCast<ToDuration>(FromDuration());

    ASSERT_THAT(decltype(duration)::period::den, Eq(1000));
}

TEST(DurationCast, AdjustsTickCount) {
    constexpr auto NUM_SECONDS_PER_HOUR = 60 * 60;

    constexpr auto duration = durationCast<Seconds>(Hours(3));

    ASSERT_THAT(duration.count(), Eq(3 * NUM_SECONDS_PER_HOUR));
}

TEST(ConversionConstruction, AdjustsTickCount) {
    Duration<float> duration(Milliseconds(3843));

    ASSERT_THAT(duration.count(), FloatEq(3.843f));
}

TEST(Numeric, Zero) {
    ASSERT_THAT(Duration<float>::zero(), Eq(Duration<float>(0.0f)));
}

TEST(Numeric, Min) {
    ASSERT_THAT(Duration<float>::min(), 
                Eq(Duration<float>(std::numeric_limits<float>::lowest())));
}

TEST(Numeric, Max) {
    ASSERT_THAT(Duration<float>::max(), 
                Eq(Duration<float>(std::numeric_limits<float>::max())));
}

TEST(Operator, Positive) {
    ASSERT_THAT(+Seconds(-2), Eq(Seconds(-2)));
}

TEST(Operator, Negation) {
    ASSERT_THAT(-Seconds(3), Eq(Seconds(-3)));
}

TEST(Operator, PreIncrement) {
    Seconds duration(4);
    ASSERT_THAT(++duration, Eq(Seconds(5)));
}

TEST(Operator, PostIncrement) {
    Seconds duration(4);
    ASSERT_THAT(duration++, Eq(Seconds(4)));
    ASSERT_THAT(duration, Eq(Seconds(5)));
}

TEST(Operator, PreDecrement) {
    Seconds duration(2);
    ASSERT_THAT(--duration, Eq(Seconds(1)));
}

TEST(Operator, PostDecrement) {
    Seconds duration(2);
    ASSERT_THAT(duration--, Eq(Seconds(2)));
    ASSERT_THAT(duration, Eq(Seconds(1)));
}

TEST(Operator, AdditionAssignment) {
    Seconds duration(2);
    ASSERT_THAT(duration += Seconds(5), Eq(Seconds(7)));
}

TEST(Operator, SubtractionAssignment) {
    Seconds duration(8);
    ASSERT_THAT(duration -= Seconds(5), Eq(Seconds(3)));
}

TEST(Operator, MultiplicationAssignment) {
    Seconds duration(8);
    ASSERT_THAT(duration *= 4, Eq(Seconds(32)));
}

TEST(Operator, DivisionAssignment) {
    Seconds duration(8);
    ASSERT_THAT(duration /= 4, Eq(Seconds(2)));
}

TEST(Operator, ModulusAssignment) {
    Seconds duration(9);
    ASSERT_THAT(duration %= 5, Eq(Seconds(4)));
}

TEST(Operator, Addition) {
    ASSERT_THAT(Duration<float>(1.63f) + Milliseconds(2358),
                Eq(Milliseconds(3988)));
}

TEST(Operator, Subtraction) {
    ASSERT_THAT(Duration<float>(1.63f) - Milliseconds(510),
                Eq(Duration<float>(1.12)));
}

TEST(Operator, MultiplyDurationByValue) {
    ASSERT_THAT(Seconds(4) * 3.2f,
                Eq(Duration<float>(12.8f)));
}

TEST(Operator, MultiplyValueByDuration) {
    ASSERT_THAT(2.1f * Seconds(4),
                Eq(Duration<float>(8.4f)));
}

TEST(Operator, DivideDurationByValue) {
    ASSERT_THAT(Seconds(1) / 2.0f,
                Eq(Milliseconds(500)));
}

TEST(Operator, DivideDurationByDuration) {
    ASSERT_THAT(Milliseconds(100) / Duration<float>(4),
                FloatEq(0.025f));
}

TEST(Operator, ModulusDurationByValue) {
    ASSERT_THAT(Milliseconds(10) % 7,
                Milliseconds(3));
}

TEST(Operator, ModulusDurationByDuration) {
    ASSERT_THAT(Seconds(10) % Milliseconds(3000),
                Eq(Seconds(1)));
}

TEST(Comparison, Equality) {
    ASSERT_TRUE(Duration<float>(4.21) == Milliseconds(4210));
}

TEST(Comparison, InEquality) {
    ASSERT_TRUE(Milliseconds(4000) != Milliseconds(4001));
}

TEST(Comparison, Less) {
    ASSERT_TRUE(Milliseconds(5001) < Duration<float>(5.002));
}

TEST(LessEqual, ReturnsTrueIfLess) {
    ASSERT_TRUE(Milliseconds(5001) <= Duration<float>(5.002));
}

TEST(LessEqual, ReturnsTrueIfEqual) {
    ASSERT_TRUE(Milliseconds(5002) <= Duration<float>(5.002));
}

TEST(Comparison, Greater) {
    ASSERT_TRUE(Milliseconds(5003) > Duration<float>(5.002));
}

TEST(GreaterEqual, ReturnsTrueIfGreater) {
    ASSERT_TRUE(Milliseconds(5003) >= Duration<float>(5.002));
}

TEST(GreaterEqual, ReturnsTrueIfEqual) {
    ASSERT_TRUE(Milliseconds(5003) >= Duration<float>(5.003));
}
