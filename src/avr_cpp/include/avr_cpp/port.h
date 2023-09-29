#pragma once

namespace avr_cpp {

template<typename T>
class Port {
public:
    Port(volatile T &dataDirection, volatile T &inputPins, volatile T &outputPins);

    void configurePins(T pinConfiguration);

    template<typename... Pins>
    void configureInputPins(Pins... pins);

    template<typename... Pins>
    void configureOutputPins(Pins... pins);

    void setInputPinPullupResistors(T pullupConfiguration);

    template<typename... Pins>
    void disableInputPinPullupResistors(Pins... pins);

    template<typename... Pins>
    void enableInputPinPullupResistors(Pins... pins);

    bool readInputPin(unsigned int pin) const;

    void setOutputPins(T pinState);

    template<typename... Pins>
    void setOutputPinsLow(Pins... pins);

    template<typename... Pins>
    void setOutputPinsHigh(Pins... pins);

    template<typename... Pins>
    void toggleOutputPins(Pins... pins);

private:
    volatile T &dataDirection;
    volatile T &inputPins;
    volatile T &outputPins;
};

template<typename T>
Port<T> makePort(volatile T &dataDirection, volatile T &inputPins, volatile T &outputPins);

} // namespace avr_cpp

#include "port_impl.h"