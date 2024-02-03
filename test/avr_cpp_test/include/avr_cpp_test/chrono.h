#pragma once

#include <ostream>

#include <avr_cpp/chrono.h>

namespace avr_cpp {
namespace Chrono {

// Helper function for printing Duration values during tests
template<typename Rep, typename Period>
std::ostream &operator<<(std::ostream &os, const Duration<Rep, Period> &d) {
    using Dur = Duration<Rep, Period>;
    os << "Duration<" 
        << typeid(typename Dur::rep).name() << ", " 
        << "ratio<" << Dur::period::num << ", " << Dur::period::den << ">>"
        << '(' << d.count() << ')';
    return os;
}

} // namespace Chrono
} // namespace avr_cpp
