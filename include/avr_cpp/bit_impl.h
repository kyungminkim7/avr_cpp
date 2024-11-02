#include <limits.h>

namespace avr_cpp {

template<typename T, typename Bit>
bool isBitInRange(Bit bit) {
    return bit >= Bit{0} && 
        bit < static_cast<Bit>(sizeof(T)) * static_cast<Bit>(CHAR_BIT);
}

template<typename T, typename... Bits>
T createBitMask(Bits... bits) {
    return (... | (T{1} << bits));
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

template<typename T, typename... Bits>
void toggleBits(T &value, Bits... bits) {
    value ^= createBitMask<T>(bits...);
}

template<typename T>
bool getBit(const T &value, unsigned int bit) {
    return value & createBitMask<T>(bit);
}

} // namespace avr_cpp