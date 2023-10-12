#pragma once

#include <stdint.h>

#include <etl/type_traits.h>

#include <avr_cpp/type_traits.h>

namespace avr_cpp {

template<unsigned long Num, unsigned long Den = 1ul>
struct Ratio {
    static_assert(Den != 0, "denominator cannot be zero");

    static constexpr unsigned long num = Num * Sign<Den>::value /
        GreatestCommonDivisor<Num, Den>::value;

    static constexpr unsigned long den = AbsoluteValue<Den>::value /
        GreatestCommonDivisor<Num, Den>::value;

    using type = Ratio<num, den>;
};

template<unsigned long Num, unsigned long Den>
constexpr unsigned long Ratio<Num, Den>::num;

template<unsigned long Num, unsigned long Den>
constexpr unsigned long Ratio<Num, Den>::den;

template<typename>
struct IsRatio : etl::false_type { };

template<unsigned long Num, unsigned long Den>
struct IsRatio<Ratio<Num, Den>> : etl::true_type { };

template<typename R1, typename R2>
struct MultiplyT {
private:
    static constexpr auto gcd1 = GreatestCommonDivisor<R1::num, R2::den>::value;
    static constexpr auto gcd2 = GreatestCommonDivisor<R2::num, R1::den>::value;

public:
    using type = Ratio<
        (R1::num / gcd1) * (R2::num / gcd2),
        (R1::den / gcd2) * (R2::den / gcd1)>;

    static constexpr auto num = type::num;
    static constexpr auto den = type::den;
};

template<typename R1, typename R2>
using Multiply = typename MultiplyT<R1, R2>::type;

template<typename R1, typename R2>
struct DivideT {
    static_assert(R2::num != 0, "division by 0");

    using type = Multiply<R1, Ratio<R2::den, R2::num>>;

    static constexpr auto num = type::num;
    static constexpr auto den = type::den;
};

template<typename R1, typename R2>
using Divide = typename DivideT<R1, R2>::type;

using Micro = Ratio<1, 1000000>;
using Milli = Ratio<1, 1000>;
using Centi = Ratio<1, 100>;
using Deci  = Ratio<1, 10>;
using Deca  = Ratio<10, 1>;
using Hecto = Ratio<100, 1>;
using Kilo  = Ratio<1000, 1>;
using Mega  = Ratio<1000000, 1>;

} // namespace avr_cpp