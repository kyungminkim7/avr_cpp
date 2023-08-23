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

    default:
        break;
    }
}
    
} // namespace

namespace avr_cpp {

AnalogDigitalConverter::AnalogDigitalConverter(AnalogDigitalConverter::VoltageReference voltageReference,
                                               AnalogDigitalConverter::ClockPrescaler clockPrescaler) {
    setVoltageReference(voltageReference);
    setClockPrescaler(clockPrescaler);
}

} // namespace avr_cpp