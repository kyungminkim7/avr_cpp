#include <avr/io.h>
#include <util/delay.h>

#include <etl/string.h>
#include <etl/to_string.h>
#include <etl/vector.h>

#include <avr_cpp/analog_digital_converter.h>
#include <avr_cpp/port.h>
#include <avr_cpp/usart0.h>


using namespace avr_cpp;

int main() {
    Port<> port(DDRB, PINB, PORTB);
    port.configureOutputPins(0, 1, 2);
    port.setOutputPinsHigh(0, 1);

    Usart0 usart(Usart::DataSize::EightBits,
                 Usart::NumStopBits::One, 9600);

    AnalogDigitalConverter adc(AnalogDigitalConverter::VoltageReference::AVCC,
                               AnalogDigitalConverter::ClockPrescaler::Eight,
                               AnalogDigitalConverter::TriggerMode::Auto,
                               AnalogDigitalConverter::AdjustResult::Left);
    adc.startConversion();

    etl::string<8> valueStr;

    while (true) {

        etl::to_string(adc.getResultHighByte(), valueStr);
        usart << "ADC: " << valueStr << ' ';

        _delay_ms(50);
    }

    return 0;
}