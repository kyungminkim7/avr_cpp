#pragma once

#include <stdint.h>

#include "abstract.h"

namespace avr_cpp {

template<typename T = uint8_t>
class DigitalPinBank {
public:
    DigitalPinBank(volatile T &pinModes, volatile T &pins);

    template<typename... PinNumbers>
    void configureInputPins(PinNumbers... pins);

    template<typename... PinNumbers>
    void configureOutputPins(PinNumbers... pins);

    bool readPin(unsigned int pin);
    void writePin(unsigned int pin, bool value);

private:
    bool isOutputPin(unsigned int pin);
    bool isInputPin(unsigned int pin);

    volatile T &pinModes;
    volatile T &pins;
};

} // namespace avr_cpp

#include "digital_pin_bank_impl.h"