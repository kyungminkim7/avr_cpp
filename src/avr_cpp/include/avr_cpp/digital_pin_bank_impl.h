#include "bit_op.h"

namespace avr_cpp {

template<typename T>
DigitalPinBank<T>::DigitalPinBank(volatile T &pinModes, volatile T &pins) : 
    pinModes(pinModes), pins(pins) {}

template<typename T>
template<typename... PinNumbers>
void DigitalPinBank<T>::configureInputPins(PinNumbers... pinNumbers) {
    unsetBitsInRange(pinModes, pinNumbers...);
}

template<typename T>
template<typename... PinNumbers>
void DigitalPinBank<T>::configureOutputPins(PinNumbers... pinNumbers) {
    setBitsInRange(pinModes, pinNumbers...);
}

template<typename T>
bool DigitalPinBank<T>::isOutputPin(unsigned int pin) {
    return getBit(pinModes, pin);
}

template<typename T>
bool DigitalPinBank<T>::isInputPin(unsigned int pin) {
    return !isOutputPin(pin);
}

template<typename T>
bool DigitalPinBank<T>::readPin(unsigned int pin) {
    return isBitInRange<T>(pin) && 
        isInputPin(pin) && 
        getBit(pins, pin);
}

template<typename T>
void DigitalPinBank<T>::writePin(unsigned int pin, bool value) {
    if (isBitInRange<T>(pin) && isOutputPin(pin)) {
        value ? 
            setBits(pins, pin) : 
            unsetBits(pins, pin);
    }
}

} // namespace avr_cpp