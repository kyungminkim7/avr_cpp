#pragma once

#include <ostream>

#include <gtest/gtest.h>

namespace avr_cpp {

class IsDivisibleByMatcher {
public:
    using is_gtest_matcher = void;

    explicit IsDivisibleByMatcher(int divisor1, int divisor2);
    
    bool MatchAndExplain(int n, std::ostream *os) const;
    void DescribeTo(std::ostream *os) const;
    void DescribeNegationTo(std::ostream *os) const;

private:
    const int divisor1;
    const int divisor2;
};

::testing::Matcher<int> IsDivisibleBy(int divisor1, int divisor2);

} // namespace avr_cpp