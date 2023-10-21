#pragma once

#include <stdint.h>

#include <etl/type_traits.h>

namespace avr_cpp {

template<intmax_t N>
struct Sign : etl::integral_constant<intmax_t, (N < 0) ? -1 : 1> {};

template<intmax_t N>
struct AbsoluteValue : etl::integral_constant<intmax_t, N * Sign<N>::value> { };

template<intmax_t M, intmax_t N>
struct GreatestCommonDivisor : GreatestCommonDivisor<N, (M % N)> { };

template<intmax_t N>
struct GreatestCommonDivisor<N, 0> 
    : etl::integral_constant<intmax_t, AbsoluteValue<N>::value> { };

template<intmax_t N>
struct GreatestCommonDivisor<0, N> 
    : etl::integral_constant<intmax_t, AbsoluteValue<N>::value> { };

template<typename T, bool = etl::is_enum<T>::value>
struct UnderlyingTypeImpl {
    using type = __underlying_type(T);
};

template<typename T>
struct UnderlyingTypeImpl<T, false> { };

template<typename T>
struct UnderlyingTypeT : public UnderlyingTypeImpl<T> {};

template<typename T>
using UnderlyingType = typename UnderlyingTypeT<T>::type;

} // namespace avr_cpp