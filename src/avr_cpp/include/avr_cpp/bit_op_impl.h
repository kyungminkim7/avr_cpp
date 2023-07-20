#include <limits.h>

namespace avr_cpp {

template<typename T, typename Bit>
bool isBitInRange(Bit bit) {
    return bit >= static_cast<Bit>(0) && 
        bit < static_cast<Bit>(sizeof(T)) * static_cast<Bit>(CHAR_BIT);
}

template<typename T, typename Bit>
T createBitMask(Bit bit) {
    return static_cast<T>(1) << bit;
}

template<typename T, typename Bit, typename... Bits>
T createBitMask(Bit bit, Bits... bits) {
    return createBitMask<T>(bit) | createBitMask<T>(bits...);
}

template<typename T, typename... Bits>
void setBits(T &value, Bits... bits) {
    value |= createBitMask<T>(bits...);
}

template<typename T, typename Bit>
void setBitsInRange(T &value, Bit bit) { 
    if (isBitInRange<T>(bit)) {
        setBits(value, bit);
    }
}

template<typename T, typename Bit, typename... Bits>
void setBitsInRange(T &value, Bit bit, Bits... bits) {
    setBitsInRange(value, bit);
    setBitsInRange(value, bits...);
}

template<typename T, typename... Bits>
void unsetBits(T &value, Bits... bits) { 
    value &= ~createBitMask<T>(bits...);
}

template<typename T, typename Bit>
void unsetBitsInRange(T &value, Bit bit) {
    if (isBitInRange<T>(bit)) {
        unsetBits(value, bit);
    }
}

template<typename T, typename Bit, typename... Bits>
void unsetBitsInRange(T &value, Bit bit, Bits... bits) {
    unsetBitsInRange(value, bit);
    unsetBitsInRange(value, bits...);
}

template<typename T>
bool getBit(const T &value, unsigned int bit) {
    return value & createBitMask<T>(bit);
}

template<typename T>
bool areAllBitsSet(const T &value) {
    return value == static_cast<T>(
        ~static_cast<T>(0));
}

template<typename T, typename Bit>
bool areAllBitsSet(const T &value, Bit bit) {
    return getBit(value, bit);
}

template<typename T, typename Bit, typename... Bits>
bool areAllBitsSet(const T &value, Bit bit, Bits... bits) {
    return areAllBitsSet(value, bit) && areAllBitsSet(value, bits...);
}

template<typename T>
bool areAllBitsUnset(const T &value) {
    return value == static_cast<T>(0);
}

template<typename T, typename Bit>
bool areAllBitsUnset(const T &value, Bit bit) {
    return !getBit(value, bit);
}

template<typename T, typename Bit, typename... Bits>
bool areAllBitsUnset(const T &value, Bit bit, Bits... bits) {
    return areAllBitsUnset(value, bit) && areAllBitsUnset(value, bits...);
}

} // namespace avr_cpp