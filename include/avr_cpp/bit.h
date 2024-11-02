#pragma once

namespace avr_cpp {

template<typename T, typename Bit>
bool isBitInRange(Bit bit);

template<typename T, typename... Bits>
T createBitMask(Bits... bits);

template<typename T, typename... Bits>
void setBits(T &value, Bits... bits);

template<typename T, typename Bit>
void setBitsInRange(T &value, Bit bit);

template<typename T, typename Bit, typename... Bits>
void setBitsInRange(T &value, Bit bit, Bits... bits);

template<typename T, typename... Bits>
void unsetBits(T &value, Bits... bits);

template<typename T, typename Bit>
void unsetBitsInRange(T &value, Bit bit);

template<typename T, typename Bit, typename... Bits>
void unsetBitsInRange(T &value, Bit bit, Bits... bits);

template<typename T, typename... Bits>
void toggleBits(T &value, Bits... bits);

template<typename T>
bool getBit(const T &value, unsigned int bit);

} // namespace avr_cpp

#include "bit_impl.h"