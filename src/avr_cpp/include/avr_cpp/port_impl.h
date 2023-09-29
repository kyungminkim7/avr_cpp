#include "bit.h"

namespace avr_cpp {

template<typename T>
Port<T>::Port(volatile T &dataDirection, 
              volatile T &inputPins, volatile T &outputPins) : 
    dataDirection(dataDirection), inputPins(inputPins), outputPins(outputPins) {}

template<typename T>
void Port<T>::configurePins(T pinConfiguration) {
    dataDirection = pinConfiguration;
}

template<typename T>
template<typename... Pins>
void Port<T>::configureInputPins(Pins... pins) {
    unsetBits(dataDirection, pins...);
}

template<typename T>
template<typename... Pins>
void Port<T>::configureOutputPins(Pins... pins) {
    setBits(dataDirection, pins...);
}

template<typename T>
void Port<T>::setInputPinPullupResistors(T pullupConfiguration) {
    outputPins = pullupConfiguration;
}

template<typename T>
template<typename... Pins>
void Port<T>::disableInputPinPullupResistors(Pins... pins) {
    unsetBits(outputPins, pins...);
}

template<typename T>
template<typename... Pins>
void Port<T>::enableInputPinPullupResistors(Pins... pins) {
    setBits(outputPins, pins...);
}

template<typename T>
bool Port<T>::readInputPin(unsigned int pin) const {
    return getBit(inputPins, pin);
}

template<typename T>
void Port<T>::setOutputPins(T pinState) {
    outputPins = pinState;
}

template<typename T>
template<typename... Pins>
void Port<T>::setOutputPinsLow(Pins... pins) {
    unsetBits(outputPins, pins...);
}

template<typename T>
template<typename... Pins>
void Port<T>::setOutputPinsHigh(Pins... pins) {
    setBits(outputPins, pins...);
}

template<typename T>
template<typename... Pins>
void Port<T>::toggleOutputPins(Pins... pins) {
    toggleBits(outputPins, pins...);
}

template<typename T>
Port<T> makePort(volatile T &dataDirection, volatile T &inputPins, volatile T &outputPins) {
    return Port<T>(dataDirection, inputPins, outputPins);
}

} // namespace avr_cpp