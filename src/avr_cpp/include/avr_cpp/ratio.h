#pragma once

#include <stdint.h>

#include <etl/type_traits.h>
#include <etl/ratio.h>

#include <avr_cpp/type_traits.h>

namespace avr_cpp {

template<typename>
struct IsRatio : etl::false_type { };

template<size_t Num, size_t Den>
struct IsRatio<etl::ratio<Num, Den>> : etl::true_type { };

template<typename R>
struct ReduceT {
    using type = etl::ratio<
        R::num * Sign<R::den>::value / GreatestCommonDivisor<R::num, R::den>::value,
        AbsoluteValue<R::den>::value / GreatestCommonDivisor<R::num, R::den>::value>;
};

template<typename R>
using Reduce = typename ReduceT<R>::type;

template<typename R1, typename R2>
struct MultiplyT {
private:
    static constexpr auto gcd1 = GreatestCommonDivisor<R1::num, R2::den>::value;
    static constexpr auto gcd2 = GreatestCommonDivisor<R2::num, R1::den>::value;

public:
    using type = etl::ratio<
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

    using type = Multiply<R1, etl::ratio<R2::den, R2::num>>;

    static constexpr auto num = type::num;
    static constexpr auto den = type::den;
};

template<typename R1, typename R2>
using Divide = typename DivideT<R1, R2>::type;

} // namespace avr_cpp