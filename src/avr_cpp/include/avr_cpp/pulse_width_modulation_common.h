#pragma once

#include "type_traits.h"

namespace avr_cpp {
namespace PulseWidthModulation {

enum class Channel {
    A = 1,
    B = 2
};

constexpr Channel operator&(Channel lhs, Channel rhs) noexcept {
    return static_cast<Channel>(
        static_cast<UnderlyingType<Channel>>(lhs) &
        static_cast<UnderlyingType<Channel>>(rhs)
    );
}

constexpr Channel operator|(Channel lhs, Channel rhs) noexcept {
    return static_cast<Channel>(
        static_cast<UnderlyingType<Channel>>(lhs) |
        static_cast<UnderlyingType<Channel>>(rhs)
    );
}

constexpr Channel operator^(Channel lhs, Channel rhs) noexcept {
    return static_cast<Channel>(
        static_cast<UnderlyingType<Channel>>(lhs) ^
        static_cast<UnderlyingType<Channel>>(rhs)
    );
}

constexpr Channel operator~(Channel channel) noexcept {
    return static_cast<Channel>(
        ~static_cast<UnderlyingType<Channel>>(channel)
    );
}

inline Channel& operator&=(Channel &lhs, Channel rhs) noexcept {
    return lhs = lhs & rhs;
}

inline Channel& operator|=(Channel &lhs, Channel rhs) noexcept {
    return lhs = lhs | rhs;
}

inline Channel& operator^=(Channel &lhs, Channel rhs) noexcept {
    return lhs = lhs ^ rhs;
}

} // namespace PulseWidthModulation
} // namespace avr_cpp