#include <avr_cpp/analog_digital_converter.h>

#include <avr/io.h>

#include <avr_cpp/bit_op.h>

namespace {

using namespace avr_cpp;

void setVoltageReference(AnalogDigitalConverter::VoltageReference voltageReference) {
    switch (voltageReference) {
    case AnalogDigitalConverter::VoltageReference::AREF:
        unsetBits(ADMUX, REFS1, REFS0);
        break;

    case AnalogDigitalConverter::VoltageReference::AVCC:
        unsetBits(ADMUX, REFS1);
        setBits(ADMUX, REFS0);
        break;

    case AnalogDigitalConverter::VoltageReference::Internal1_1V:
        setBits(ADMUX, REFS1, REFS0);
        break;
    
    default:
        break;
    }
}

void setClockPrescaler(AnalogDigitalConverter::ClockPrescaler clockPrescaler) {
    switch (clockPrescaler) {
    case AnalogDigitalConverter::ClockPrescaler::Two:
        unsetBits(ADCSRA, ADPS2, ADPS1, ADPS0);
        break;

    case AnalogDigitalConverter::ClockPrescaler::Four:
        unsetBits(ADCSRA, ADPS2, ADPS0);
        setBits(ADCSRA, ADPS1);
        break;

    case AnalogDigitalConverter::ClockPrescaler::Eight:
        unsetBits(ADCSRA, ADPS2);
        setBits(ADCSRA, ADPS1, ADPS0);
        break;

    case AnalogDigitalConverter::ClockPrescaler::Sixteen:
        unsetBits(ADCSRA, ADPS1, ADPS0);
        setBits(ADCSRA, ADPS2);
        break;

    case AnalogDigitalConverter::ClockPrescaler::ThirtyTwo:
        unsetBits(ADCSRA, ADPS1);
        setBits(ADCSRA, ADPS2, ADPS0);
        break;

    case AnalogDigitalConverter::ClockPrescaler::SixtyFour:
        unsetBits(ADCSRA, ADPS0);
        setBits(ADCSRA, ADPS2, ADPS1);
        break;

    case AnalogDigitalConverter::ClockPrescaler::OneHundredTwentyEight:
        setBits(ADCSRA, ADPS2, ADPS1, ADPS0);
        break;

    default:
        break;
    }
}

void setTriggerMode(AnalogDigitalConverter::TriggerMode triggerMode) {
    switch (triggerMode) {
    case AnalogDigitalConverter::TriggerMode::Single:
        unsetBits(ADCSRA, ADATE);
        break;

    case AnalogDigitalConverter::TriggerMode::Auto:
        setBits(ADCSRA, ADATE);
        break;
    
    default:
        break;
    }
}

void setAdjustResult(AnalogDigitalConverter::AdjustResult adjustResult) {
    switch (adjustResult) {
    case AnalogDigitalConverter::AdjustResult::Right:
        unsetBits(ADMUX, ADLAR);
        break;

    case AnalogDigitalConverter::AdjustResult::Left:
        setBits(ADMUX, ADLAR);
        break;
    
    default:
        break;
    }
}

void enableAnalogDigitalConverter() {
    setBits(ADCSRA, ADEN);
}
    
} // namespace

namespace avr_cpp {

AnalogDigitalConverter::AnalogDigitalConverter(AnalogDigitalConverter::VoltageReference voltageReference,
                                               AnalogDigitalConverter::ClockPrescaler clockPrescaler,
                                               AnalogDigitalConverter::TriggerMode triggerMode,
                                               AnalogDigitalConverter::AdjustResult adjustResult) {
    setVoltageReference(voltageReference);
    setClockPrescaler(clockPrescaler);
    setTriggerMode(triggerMode);
    setAdjustResult(adjustResult);

    enableAnalogDigitalConverter();
}

AnalogDigitalConverter::~AnalogDigitalConverter() {
    unsetBits(ADCSRA, ADEN);
}

void AnalogDigitalConverter::startConversion() {
    setBits(ADCSRA, ADSC);
}

bool AnalogDigitalConverter::isConversionInProgress() const {
    return getBit(ADCSRA, ADSC);
}

uint16_t AnalogDigitalConverter::getResult() const {
    return ADC;
}

uint8_t AnalogDigitalConverter::getResultHighByte() const {
    return ADCH;
}

uint8_t AnalogDigitalConverter::getResultLowByte() const {
    return ADCL;
}

void AnalogDigitalConverter::setChannel(int channel) {
    ADMUX &= 0xf0;
    ADMUX |= channel;
}

} // namespace avr_cpp