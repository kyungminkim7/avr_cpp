#pragma once

#include <stdint.h>

#include <etl/limits.h>
#include <etl/type_traits.h>

#include "ratio.h"

namespace avr_cpp {
namespace Chrono {

class SystemClock {
public:
    static constexpr auto frequency = F_CPU;
};

template<typename Rep, typename Period = Ratio<1>>
struct Duration;

// common_type specializations
template<typename Rep, typename Period1, typename Period2, typename = void>
struct DurationCommonType {};

template<typename Rep, typename Period1, typename Period2>
struct DurationCommonType<Rep, Period1, Period2, 
                          etl::void_t<typename Rep::type>>
{
private:
    using gcdNum = GreatestCommonDivisor<Period1::num, Period2::num>;
    using gcdDen = GreatestCommonDivisor<Period1::den, Period2::den>;
    using period = Ratio<gcdNum::value,
                         (Period1::den / gcdDen::value) * Period2::den>;

public:
    using type = Duration<typename Rep::type, period>;
};

} // namespace Chrono
} // namespace avr_cpp

// common_type specializations
namespace etl {

template<typename Rep1, typename Period1, typename Rep2, typename Period2>
struct common_type<avr_cpp::Chrono::Duration<Rep1, Period1>,
                   avr_cpp::Chrono::Duration<Rep2, Period2>> 
    : avr_cpp::Chrono::DurationCommonType<etl::common_type<Rep1, Rep2>, 
                                          Period1, Period2> {};

template<typename Rep, typename Period>
struct common_type<avr_cpp::Chrono::Duration<Rep, Period>,
                   avr_cpp::Chrono::Duration<Rep, Period>> {
    using type = avr_cpp::Chrono::Duration<common_type_t<Rep>, Period>;
};

template<typename Rep, typename Period>
struct common_type<avr_cpp::Chrono::Duration<Rep, Period>> {
    using type = avr_cpp::Chrono::Duration<common_type_t<Rep>, Period>;
};

} // namespace etl

namespace avr_cpp {
namespace Chrono {

template<typename>
struct IsDuration : etl::false_type { };

template<typename Rep, typename Period>
struct IsDuration<Duration<Rep, Period>> : etl::true_type { };

template<typename T>
using enableIfIsDuration = etl::enable_if_t<IsDuration<T>::value, T>;

template<typename T>
using disableIfIsDuration = etl::enable_if_t<!IsDuration<T>::value, T>;

template<typename ToDuration, typename FromRep, typename FromPeriod, 
         typename = enableIfIsDuration<ToDuration>>
constexpr ToDuration durationCast(const Duration<FromRep, FromPeriod> &d);

// Distance between two points in time
template<typename Rep, typename Period>
struct Duration {
	static_assert(etl::is_arithmetic<Rep>::value, "Rep must be an arithmetic type");
	static_assert(IsRatio<Period>::value, "Period must be a specialization of ratio");

public:
	using rep = Rep;
	using period = typename Period::type;

    template<typename Period2>
    using isHarmonic = etl::bool_constant<
        Divide<Period2, period>::den == 1>;

	constexpr Duration() = default;
	Duration(const Duration&) = default;

	template<typename Rep2, typename = etl::enable_if_t<etl::conjunction<
		etl::is_convertible<const Rep2&, rep>,
		etl::disjunction<etl::is_floating_point<rep>, 
		  				 etl::negation<etl::is_floating_point<Rep2>>>>::value>>
    constexpr explicit Duration(const Rep2& ticks);

    template<typename Rep2, typename Period2, typename = etl::enable_if_t<etl::conjunction<
        etl::is_convertible<const Rep2&, rep>, 
        etl::disjunction<etl::is_floating_point<rep>,
                         etl::conjunction<isHarmonic<Period2>,
                                          etl::negation<etl::is_floating_point<Rep2>>>>>::value>>
    constexpr Duration(const Duration<Rep2, Period2> &d);

	~Duration() = default;

	Duration& operator=(const Duration&) = default;

	constexpr Rep count() const;

	constexpr Duration<etl::common_type_t<rep>, period> operator+() const {
        return Duration<etl::common_type_t<rep>, period>(ticks); 
    }

	constexpr Duration<etl::common_type_t<rep>, period> operator-() const {
        return Duration<etl::common_type_t<rep>, period>(-ticks); 
    }

    Duration& operator++() {
        ++ticks;
        return *this;
    }

    Duration operator++(int) {
        return Duration(ticks++);
    }

    Duration& operator--() {
        --ticks;
        return *this;
    }

    Duration operator--(int) {
        return Duration(ticks--);
    }

    Duration& operator+=(const Duration &other) {
        ticks += other.count();
        return *this;
    }

    Duration& operator-=(const Duration &other) {
        ticks -= other.count();
        return *this;
    }

    Duration& operator*=(const rep &multiplier) {
        ticks *= multiplier;
        return *this;
    }

    Duration& operator/=(const rep &multiplier) {
        ticks /= multiplier;
        return *this;
    }

    Duration& operator%=(const rep &multiplier) {
        ticks %= multiplier;
        return *this;
    }

    static constexpr Duration zero() noexcept {
        return Duration(rep(0));
    }

    static constexpr Duration min() noexcept {
        return Duration(etl::numeric_limits<rep>::lowest());
    }

    static constexpr Duration max() noexcept {
        return Duration(etl::numeric_limits<rep>::max());
    }

private:
	rep ticks{};
};

template<typename Rep1, typename Period1,
         typename Rep2, typename Period2>
constexpr etl::common_type_t<Duration<Rep1, Period1>,
                             Duration<Rep2, Period2>>
operator+(const Duration<Rep1, Period1> &lhs,
          const Duration<Rep2, Period2> &rhs);

template<typename Rep1, typename Period1,
         typename Rep2, typename Period2>
constexpr etl::common_type_t<Duration<Rep1, Period1>,
                             Duration<Rep2, Period2>>
operator-(const Duration<Rep1, Period1> &lhs,
          const Duration<Rep2, Period2> &rhs);

template<typename Rep1, typename Period, typename Rep2,
         typename CommonRep = etl::common_type_t<Rep1, Rep2>,
         typename CommonDuration = Duration<CommonRep, Period>,
         typename = etl::enable_if_t<etl::is_convertible<const Rep2 &, CommonRep>::value>>
constexpr CommonDuration operator*(const Duration<Rep1, Period> &lhs, 
                                   const Rep2 &rhs);

template<typename Rep1, typename Rep2, typename Period,
         typename CommonRep = etl::common_type_t<Rep1, Rep2>,
         typename CommonDuration = Duration<CommonRep, Period>>
constexpr CommonDuration operator*(const Rep1 &lhs,
                                   const Duration<Rep2, Period> &rhs);

template<typename Rep1, typename Period, typename Rep2,
         typename CommonRep = etl::common_type_t<Rep1, Rep2>,
         typename CommonDuration = Duration<CommonRep, Period>,
         typename = disableIfIsDuration<Rep2>>
constexpr CommonDuration operator/(const Duration<Rep1, Period> &lhs, 
                                   const Rep2 &rhs);

template<typename Rep1, typename Period1,
         typename Rep2, typename Period2>
etl::common_type_t<Rep1, Rep2> operator/(const Duration<Rep1, Period1> &lhs,
                                         const Duration<Rep2, Period2> &rhs);

template<typename Rep1, typename Period, typename Rep2,
         typename CommonRep = etl::common_type_t<Rep1, Rep2>,
         typename CommonDuration = Duration<CommonRep, Period>,
         typename = disableIfIsDuration<Rep2>>
constexpr CommonDuration operator%(const Duration<Rep1, Period> &lhs, 
                                   const Rep2 &rhs);

template<typename Rep1, typename Period1,
         typename Rep2, typename Period2>
etl::common_type_t<Duration<Rep1, Period1>,
                   Duration<Rep2, Period2>> 
operator%(const Duration<Rep1, Period1> &lhs,
          const Duration<Rep2, Period2> &rhs);

template<typename Rep1, typename Period1,
         typename Rep2, typename Period2>
constexpr bool operator==(const Duration<Rep1, Period1> &lhs, 
                          const Duration<Rep2, Period2> &rhs);

template<typename Rep1, typename Period1,
         typename Rep2, typename Period2>
constexpr bool operator!=(const Duration<Rep1, Period1> &lhs, 
                          const Duration<Rep2, Period2> &rhs);

template<typename Rep1, typename Period1,
         typename Rep2, typename Period2>
constexpr bool operator<(const Duration<Rep1, Period1> &lhs, 
                         const Duration<Rep2, Period2> &rhs);

template<typename Rep1, typename Period1,
         typename Rep2, typename Period2>
constexpr bool operator<=(const Duration<Rep1, Period1> &lhs, 
                          const Duration<Rep2, Period2> &rhs);

template<typename Rep1, typename Period1,
         typename Rep2, typename Period2>
constexpr bool operator>(const Duration<Rep1, Period1> &lhs, 
                         const Duration<Rep2, Period2> &rhs);

template<typename Rep1, typename Period1,
         typename Rep2, typename Period2>
constexpr bool operator>=(const Duration<Rep1, Period1> &lhs, 
                          const Duration<Rep2, Period2> &rhs);

using Microseconds = Duration<intmax_t, Micro>;
using Milliseconds = Duration<intmax_t, Milli>;
using Seconds = Duration<intmax_t>;
using Minutes = Duration<intmax_t, Ratio<60>>;
using Hours = Duration<intmax_t, Ratio<3600>>;

using Days = Duration<intmax_t, Ratio<86400>>;
using Weeks = Duration<intmax_t, Ratio<604800>>;
using Months = Duration<intmax_t, Ratio<2629746>>;
using Years = Duration<intmax_t, Ratio<31556952>>;

} // namespace Chrono
} // namespace avr_cpp

#include "chrono_impl.h"