#pragma once

#include <stdint.h>

#include "abstract.h"
#include "bit_op.h"

namespace avr_cpp {

enum class PinMode {
    Input,
    Output
};

class DigitalPortIface {
public:
    virtual ~DigitalPortIface() = default;

    virtual void configurePin(unsigned int pin, PinMode mode) = 0;
    virtual bool readPin(unsigned int pin) = 0;
    virtual void writePin(unsigned int pin, bool value) = 0;
};

template<typename T>
class DigitalPort {
public:
    DigitalPort(volatile T *pinModes, volatile T *pins);

    template<typename... PinNumbers>
    void configureInputPins(PinNumbers... pins);

    template<typename... PinNumbers>
    void configureOutputPins(PinNumbers... pins);

    bool readPin(unsigned int pin);
    void writePin(unsigned int pin, bool value);

private:
    bool isInputPin(unsigned int pin);

    volatile T *pinModes;
    volatile T *pins;
};

template<typename T>
DigitalPort<T>::DigitalPort(volatile T *pinModes, volatile T *pins) : 
    pinModes(pinModes), pins(pins) {}

template<typename T>
template<typename... PinNumbers>
void DigitalPort<T>::configureInputPins(PinNumbers... pinNumbers) {
    unsetBits(*pinModes, pinNumbers...);
}

template<typename T>
template<typename... PinNumbers>
void DigitalPort<T>::configureOutputPins(PinNumbers... pinNumbers) {
    setBits(*pinModes, pinNumbers...);
}

template<typename T>
bool DigitalPort<T>::isInputPin(unsigned int pin) {
    return getBit(*pinModes, pin) == false;
}

template<typename T>
bool DigitalPort<T>::readPin(unsigned int pin) {
    return isBitInRange<T>(pin) && 
        isInputPin(pin) && 
        getBit(*pins, pin);
}

template<typename T>
void DigitalPort<T>::writePin(unsigned int pin, bool value) {
    if (!isBitInRange<T>(pin) || isInputPin(pin)) {
        return;
    }

    value ? 
        setBits(*pins, pin) : 
        unsetBits(*pins, pin);
}

} // namespace avr_cpp