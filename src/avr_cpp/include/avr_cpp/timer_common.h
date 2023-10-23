#pragma once

#include <avr_cpp/type_traits.h>

namespace avr_cpp {
namespace Timer {

enum class Mode { Repeat, SingleShot };
enum class PinMode { Toggle, Clear, Set };

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

} // namespace Timer
} // namespace avr_cpp
