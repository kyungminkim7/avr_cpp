#pragma once

namespace avr_cpp {

template<typename T, typename Bit>
bool isBitInRange(Bit bit);

template<typename T, typename Bit>
T createBitMask(Bit bit);

template<typename T, typename Bit, typename... Bits>
T createBitMask(Bit bit, Bits... bits);

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

template<typename T>
bool getBit(const T &value, unsigned int bit);

template<typename T>
bool areAllBitsSet(const T &value);

template<typename T, typename Bit, typename... Bits>
bool areAllBitsSet(const T &value, Bit bit, Bits... bits);

template<typename T>
bool areAllBitsUnset(const T &value);

template<typename T, typename Bit>
bool areAllBitsUnset(const T &value, Bit bit);

template<typename T, typename Bit, typename... Bits>
bool areAllBitsUnset(const T &value, Bit bit, Bits... bits);

} // namespace avr_cpp

#include "bit_op_impl.h"