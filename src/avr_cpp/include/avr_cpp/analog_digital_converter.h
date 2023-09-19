#pragma once

#include <stdint.h>

namespace avr_cpp {

class AnalogDigitalConverter {
public:
    enum class VoltageReference { AREF, AVCC, Internal1_1V };
    enum class ClockPrescaler { Two, Four, Eight, Sixteen, 
                                ThirtyTwo, SixtyFour, 
                                OneHundredTwentyEight };
    enum class TriggerMode { Single, Auto };
    enum class AdjustResult { Right, Left };

    AnalogDigitalConverter(VoltageReference voltageReference,
                           ClockPrescaler clockPrescaler,
                           TriggerMode triggerMode,
                           AdjustResult adjustResult = AdjustResult::Right);

    ~AnalogDigitalConverter();

    void startConversion();
    bool isConversionInProgress() const;

    uint16_t getResult() const;
    uint8_t getResultHighByte() const;
    uint8_t getResultLowByte() const;

    void setChannel(int channel);
};

} // namespace avr_cpp