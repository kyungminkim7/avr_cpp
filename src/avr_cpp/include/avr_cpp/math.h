#pragma once

#include <math.h>

#include <etl/type_traits.h>

namespace avr_cpp {

template<typename T>
constexpr T PI = T(3.1415926535897932385L);

// Integral modulo
template<typename T1, typename T2>
inline auto modulo(T1 dividend, T2 divisor, etl::true_type) {
    return dividend % divisor;
}

// Floating point modulo
template<typename T1, typename T2>
inline auto modulo(T1 dividend, T2 divisor, etl::false_type) {
    using T = etl::common_type_t<T1, T2>;
    return fmod(static_cast<T>(dividend), 
                static_cast<T>(divisor));
}

template<typename T1, typename T2>
inline auto modulo(T1 dividend, T2 divisor) {
    return modulo(dividend, divisor, 
        etl::conditional_t<
            etl::conjunction<
                etl::is_integral<T1>,
                etl::is_integral<T2>
            >::value,
            etl::true_type, etl::false_type
        >{});
}

} // namespace avr_cpp