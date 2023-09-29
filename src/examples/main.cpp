#include <avr/io.h>
#include <util/delay.h>

#include <etl/delegate.h>
#include <etl/string.h>
#include <etl/to_string.h>
#include <etl/vector.h>

#include <avr_cpp/analog_digital_converter.h>
#include <avr_cpp/external_interrupt.h>
#include <avr_cpp/pin_change_interrupt.h>
#include <avr_cpp/port.h>
#include <avr_cpp/usart0.h>


using namespace avr_cpp;

void isr() {

}

int main() {
    Port<> leds(DDRB, PINB, PORTB);
    leds.configureOutputPins(PB0, PB1, PB2);
    leds.setOutputPinsHigh(PB0);

    Port<> pins(DDRD, PIND, PORTD);
    pins.configureInputPins(PD2);
    pins.enableInputPinPullupResistors(PD2);

    Usart0 usart(Usart::DataSize::EightBits,
                 Usart::NumStopBits::One, 9600);

    AnalogDigitalConverter adc(AnalogDigitalConverter::VoltageReference::AVCC,
                               AnalogDigitalConverter::ClockPrescaler::Eight,
                               AnalogDigitalConverter::TriggerMode::Auto,
                               AnalogDigitalConverter::AdjustResult::Left);
    adc.startConversion();

    etl::string<8> valueStr;

    ExternalInterrupt::set(INT1, ExternalInterrupt::Sense::Change,
                           ExternalInterrupt::InterruptServiceRoutine::create<isr>());

    PinChangeInterrupt::set(PCIE0, []{}, PD1);

    while (true) {
        if (pins.readInputPin(PD2)) {
            leds.setOutputPinsLow(PB2);
        } else {
            leds.setOutputPinsHigh(PB2);
        }

        etl::to_string(adc.getResultHighByte(), valueStr);
        usart << "ADC: " << valueStr << ' ';

        _delay_ms(50);
    }

    return 0;
}