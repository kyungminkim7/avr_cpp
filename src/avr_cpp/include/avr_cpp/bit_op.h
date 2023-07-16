#pragma once

#include <limits.h>

namespace avr_cpp {

// Return whether bit position is valid for a data type
template<typename T, typename Bit>
bool isBitInRange(Bit bit) {
    return bit >= 0 && bit < sizeof(T) * CHAR_BIT;
}

// Returns a bitmask with the bit position set
template<typename T, typename Bit>
T convertBitPosition(Bit bit) {
    return 1 << bit;
}

template<typename T>
void setBits(T &value) { }

template<typename T, typename Bit, typename... Bits>
void setBits(T &value, Bit bit, Bits... bits) {
    if (isBitInRange<T>(bit)) {
        value |= convertBitPosition<T>(bit);
    }

    setBits(value, bits...);
}

template<typename T>
void unsetBits(T &value) { }

template<typename T, typename Bit, typename... Bits>
void unsetBits(T &value, Bit bit, Bits... bits) {
    if (isBitInRange<T>(bit)) {
        value &= ~convertBitPosition<T>(bit);
    }

    unsetBits(value, bits...);
}

template<typename T>
bool getBit(const T &value, unsigned int bit) {
    return value & convertBitPosition<T>(bit);
}

} // namespace avr_cpp