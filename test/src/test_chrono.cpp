#include <limits>
#include <numeric>
#include <type_traits>

#include <gmock/gmock.h>

#include <avr_cpp/chrono.h>
#include <avr_cpp_test/chrono.h>

using namespace ::testing;
using namespace avr_cpp;
using namespace avr_cpp::Chrono;

TEST(Chrono, DurationStoresRepType) {
    const auto result = std::is_same_v<typename Duration<float>::rep, 
                                       float>;
    ASSERT_TRUE(result);
}

TEST(Chrono, DurationStoresPeriodType) {
    const auto result = std::is_same_v<typename Duration<int, Milli>::period, 
                                       Milli>;
    ASSERT_TRUE(result);
}

TEST(Chrono, DurationConstructionReducesPeriod) {
    using period = Duration<int, Ratio<25, 30>>::period;
    constexpr auto gcd = std::gcd(25, 30);

    ASSERT_THAT(period::num, Eq(25 / gcd));
    ASSERT_THAT(period::den, Eq(30 / gcd));
}

TEST(Chrono, DefaultDurationConstructionSetsZeroTickCount) {
    Duration<int> duration;

    ASSERT_THAT(duration.count(), Eq(0));
}

TEST(Chrono, DurationConstructionSetsTickCount) {
    Duration<float> duration(4.2f);

    ASSERT_THAT(duration.count(), FloatEq(4.2f));
}

TEST(Chrono, InvalidDurationConstruction) {
    Duration<float> duration;
}

TEST(Chrono, IsDurationFalse) {
    ASSERT_FALSE(IsDuration<float>::value);
}

TEST(Chrono, IsDurationTrue) {
    ASSERT_TRUE(IsDuration<Duration<int>>::value);
}

TEST(Chrono, IsHarmonicReturnsFalseTypeForNonExactMultiples) {
    const auto result = Duration<int, Ratio<3, 5>>
        ::isHarmonic<Ratio<3, 5 * 2>>
        ::value;

    ASSERT_FALSE(result);
}

TEST(Chrono, IsHarmonicReturnsTrueTypeForExactMultiples) {
    const auto result = Duration<int, Ratio<3, 5>>
        ::isHarmonic<Ratio<3 * 7, 5>>
        ::value;
    ASSERT_TRUE(result);
}

TEST(Chrono, CommonDurationRepType) {
    using commonDuration = etl::common_type_t<Duration<int>, Duration<float>>;

    const auto result = std::is_same_v<commonDuration::rep, 
                                       std::common_type_t<int, float>>;
    ASSERT_TRUE(result);
}

TEST(Chrono, CommonDurationPeriodType) {
    using commonDuration = etl::common_type_t<Duration<int, Ratio<8, 9>>, 
                                              Duration<int, Ratio<14, 27>>>;

    ASSERT_THAT(commonDuration::period::num, Eq(2));
    ASSERT_THAT(commonDuration::period::den, Eq(27));
}

TEST(Chrono, CastDurationRepType) {
    using FromDuration = Duration<int>;
    using ToDuration = Duration<float>;

    constexpr auto duration = durationCast<ToDuration>(FromDuration());
    const auto result = std::is_same_v<decltype(duration)::rep, float>;

    ASSERT_TRUE(result);
}

TEST(Chrono, CastDurationPeriodType) {
    using FromDuration = Duration<int>;
    using ToDuration = Duration<int, Milli>;

    constexpr auto duration = durationCast<ToDuration>(FromDuration());

    ASSERT_THAT(decltype(duration)::period::den, Eq(1000));
}

TEST(Chrono, DurationCastAdjustsTickCount) {
    constexpr auto NUM_SECONDS_PER_HOUR = 60 * 60;

    constexpr auto duration = durationCast<Seconds>(Hours(3));

    ASSERT_THAT(duration.count(), Eq(3 * NUM_SECONDS_PER_HOUR));
}

TEST(Chrono, DurationConstructionConvertsTickCount) {
    Duration<float> duration(Milliseconds(3843));

    ASSERT_THAT(duration.count(), FloatEq(3.843f));
}

TEST(Chrono, ZeroDuration) {
    ASSERT_THAT(Duration<float>::zero(), Eq(Duration<float>(0.0f)));
}

TEST(Chrono, MinDuration) {
    ASSERT_THAT(Duration<float>::min(), 
                Eq(Duration<float>(std::numeric_limits<float>::lowest())));
}

TEST(Chrono, MaxDuration) {
    ASSERT_THAT(Duration<float>::max(), 
                Eq(Duration<float>(std::numeric_limits<float>::max())));
}

TEST(Chrono, DurationPositiveOperator) {
    ASSERT_THAT(+Seconds(-2), Eq(Seconds(-2)));
}

TEST(Chrono, DurationNegation) {
    ASSERT_THAT(-Seconds(3), Eq(Seconds(-3)));
}

TEST(Chrono, DurationPreIncrement) {
    Seconds duration(4);
    ASSERT_THAT(++duration, Eq(Seconds(5)));
}

TEST(Chrono, DurationPostIncrement) {
    Seconds duration(4);
    ASSERT_THAT(duration++, Eq(Seconds(4)));
    ASSERT_THAT(duration, Eq(Seconds(5)));
}

TEST(Chrono, DurationPreDecrement) {
    Seconds duration(2);
    ASSERT_THAT(--duration, Eq(Seconds(1)));
}

TEST(Chrono, DurationPostDecrement) {
    Seconds duration(2);
    ASSERT_THAT(duration--, Eq(Seconds(2)));
    ASSERT_THAT(duration, Eq(Seconds(1)));
}

TEST(Chrono, DurationAdditionAssignment) {
    Seconds duration(2);
    ASSERT_THAT(duration += Seconds(5), Eq(Seconds(7)));
}

TEST(Chrono, DurationSubtractionAssignment) {
    Seconds duration(8);
    ASSERT_THAT(duration -= Seconds(5), Eq(Seconds(3)));
}

TEST(Chrono, DurationMultiplicationAssignment) {
    Seconds duration(8);
    ASSERT_THAT(duration *= 4, Eq(Seconds(32)));
}

TEST(Chrono, DurationDivisionAssignment) {
    Seconds duration(8);
    ASSERT_THAT(duration /= 4, Eq(Seconds(2)));
}

TEST(Chrono, DurationModulusAssignment) {
    Seconds duration(9);
    ASSERT_THAT(duration %= 5, Eq(Seconds(4)));
}

TEST(Chrono, DurationAddition) {
    ASSERT_THAT(Duration<float>(1.63f) + Milliseconds(2358),
                Eq(Milliseconds(3988)));
}

TEST(Chrono, DurationSubtraction) {
    ASSERT_THAT(Duration<float>(1.63f) - Milliseconds(510),
                Eq(Duration<float>(1.12)));
}

TEST(Chrono, MultiplyDurationByValue) {
    ASSERT_THAT(Seconds(4) * 3.2f,
                Eq(Duration<float>(12.8f)));
}

TEST(Chrono, MultiplyValueByDuration) {
    ASSERT_THAT(2.1f * Seconds(4),
                Eq(Duration<float>(8.4f)));
}

TEST(Chrono, DivideDurationByValue) {
    ASSERT_THAT(Seconds(1) / 2.0f,
                Eq(Milliseconds(500)));
}

TEST(Chrono, DivideDurationByDuration) {
    ASSERT_THAT(Milliseconds(100) / Duration<float>(4),
                FloatEq(0.025f));
}

TEST(Chrono, ModulusDurationByValue) {
    ASSERT_THAT(Milliseconds(10) % 7,
                Milliseconds(3));
}

TEST(Chrono, ModulusDurationByDuration) {
    ASSERT_THAT(Seconds(10) % Milliseconds(3000),
                Eq(Seconds(1)));
}

TEST(Chrono, DurationEquality) {
    ASSERT_TRUE(Duration<float>(4.21) == Milliseconds(4210));
}

TEST(Chrono, DurationInEquality) {
    ASSERT_TRUE(Milliseconds(4000) != Milliseconds(4001));
}

TEST(Chrono, DurationLess) {
    ASSERT_TRUE(Milliseconds(5001) < Duration<float>(5.002));
}

TEST(Chrono, DurationLessEqualReturnsTrueIfLess) {
    ASSERT_TRUE(Milliseconds(5001) <= Duration<float>(5.002));
}

TEST(Chrono, DurationLessEqualReturnsTrueIfEqual) {
    ASSERT_TRUE(Milliseconds(5002) <= Duration<float>(5.002));
}

TEST(Chrono, DurationGreater) {
    ASSERT_TRUE(Milliseconds(5003) > Duration<float>(5.002));
}

TEST(Chrono, DurationGreaterEqualReturnsTrueIfGreater) {
    ASSERT_TRUE(Milliseconds(5003) >= Duration<float>(5.002));
}

TEST(Chrono, DurationGreaterEqualReturnsTrueIfEqual) {
    ASSERT_TRUE(Milliseconds(5003) >= Duration<float>(5.003));
}
