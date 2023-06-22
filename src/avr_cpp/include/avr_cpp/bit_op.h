#pragma once

#include <limits.h>

namespace avr_cpp {

// Return whether bit position is valid for a data type
template<typename T>
bool isBitInRange(unsigned int bit) {
    return bit >= 0 && bit < sizeof(T) * CHAR_BIT;
}

// Returns a bitmask with the bit position set
template<typename T>
T convertBitPosition(unsigned int bit) {
    return 1 << bit;
}

template<typename T>
void setBit(T &value, unsigned int bit) {
    value |= convertBitPosition<T>(bit);
}

template<typename T>
void unsetBit(T &value, unsigned int bit) {
    value &= ~convertBitPosition<T>(bit);
}

template<typename T>
bool getBit(const T &value, unsigned int bit) {
    return value & convertBitPosition<T>(bit);
}

} // namespace avr_cpp