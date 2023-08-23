#pragma once

namespace avr_cpp {

class AnalogDigitalConverter {
public:
    enum class VoltageReference { AREF, AVCC, Internal1_1V };
    enum class ClockPrescaler { Two, Four, Eight, Sixteen, ThirtyTwo, SixtyFour };

    AnalogDigitalConverter(VoltageReference voltageReference,
                           ClockPrescaler clockPrescaler);
};

} // namespace avr_cpp