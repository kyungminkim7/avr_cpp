#include <avr_cpp/matchers.h>

namespace avr_cpp {

IsDivisibleByMatcher::IsDivisibleByMatcher(int divisor1, int divisor2) 
    : divisor1(divisor1), divisor2(divisor2) {}

bool IsDivisibleByMatcher::MatchAndExplain(int n, std::ostream *os) const {
    const auto remainder1 = n % divisor1;
    const auto remainder2 = n % divisor2;
    if (os != nullptr)
        *os << "the remainders are " << remainder1 << ", " << remainder2;
    return remainder1 == 0 && remainder2 == 0;
}

void IsDivisibleByMatcher::DescribeTo(std::ostream *os) const {
    *os << "is divisible by " << divisor1 << " & " << divisor2;
}

void IsDivisibleByMatcher::DescribeNegationTo(std::ostream *os) const {
    *os << "is not divisible by " << divisor1 << " & " << divisor2;
}

::testing::Matcher<int> IsDivisibleBy(int divisor1, int divisor2) {
    return IsDivisibleByMatcher(divisor1, divisor2);
}

} // namespace avr_cpp