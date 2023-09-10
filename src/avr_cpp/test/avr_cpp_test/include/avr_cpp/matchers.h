#pragma once

#include <ostream>
#include <tuple>

#include <avr_cpp/bit_op.h>

namespace avr_cpp {

template<typename T>
void printArgs(std::ostream *os, T arg) {
    *os << arg;
}

template<typename T, typename... Types>
void printArgs(std::ostream *os, T arg, Types... args) {
    *os << arg << ", ";
    printArgs(os, args...);
}

template<typename... T>
void printTuple(std::ostream *os, const std::tuple<T...> &value) {
    std::apply([os](T... elements){ printArgs(os, elements...); },
               value);
}

template<typename... Bits>
class BitsAreSet {
public:
    using is_gtest_matcher = void;

    explicit BitsAreSet(Bits... bits)
        : bits(bits...) {}

    template<typename T>
    bool MatchAndExplain(T value, std::ostream *os) const {
        const auto isBitSet = [os](auto value, auto bit) {
            const auto result = avr_cpp::getBit(value, bit);
            if (!result && os != nullptr) {
                *os << "bit " << bit << " is not set";
            }
            return result;
        };

        // Check bits to determine if they are set
        const auto result = std::apply(
            [value, isBitSet](Bits... bits){ 
                return ( isBitSet(value, bits) && ... );
            },
            bits);

        // Success message
        if (result && os != nullptr) {
            DescribeTo(os);
        }

        return result;
    }

    void DescribeTo(std::ostream *os) const {
        *os << "all bits are set: ";
        printTuple(os, bits);
    }

    void DescribeNegationTo(std::ostream *os) const {
        *os << "some bits are not set: ";
        printTuple(os, bits);
    }

private:
    std::tuple<Bits...> bits;
};

template<typename... Bits>
class BitsAreUnset {
public:
    using is_gtest_matcher = void;

    explicit BitsAreUnset(Bits... bits)
        : bits(bits...) {}

    template<typename T>
    bool MatchAndExplain(T value, std::ostream *os) const {
        const auto isBitUnset = [os](auto value, auto bit) {
            const auto result = !avr_cpp::getBit(value, bit);
            if (!result && os != nullptr) {
                *os << "bit " << bit << " is set";
            }
            return result;
        };

        // Check bits to determine if they are unset
        const auto result = std::apply(
            [value, isBitUnset](Bits... bits){ 
                return ( isBitUnset(value, bits) && ... ); 
            },
            bits);

        // Success message
        if (result && os != nullptr) {
            DescribeTo(os);
        }

        return result;
    }

    void DescribeTo(std::ostream *os) const {
        *os << "all bits are unset: ";
        printTuple(os, bits);
    }

    void DescribeNegationTo(std::ostream *os) const {
        *os << "some bits are set: ";
        printTuple(os, bits);
    }
private:
    std::tuple<Bits...> bits;
};

} // namespace avr_cpp