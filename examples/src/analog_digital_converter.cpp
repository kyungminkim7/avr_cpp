/*
This program is an example of using the analog digital converter (ADC) and USART.

An ADC value is continuously read and sent serially over USART.
*/

#include <avr/io.h>
#include <util/delay.h>

#include <etl/string.h>
#include <etl/to_string.h>

#include <avr_cpp/analog_digital_converter.h>
#include <avr_cpp/usart.h>

using namespace avr_cpp;

constexpr auto BAUD_RATE = 9600;

int main() {
    Usart0 usart(Usart::DataSize::EightBits,
                 Usart::NumStopBits::One, 
                 BAUD_RATE);

    AnalogDigitalConverter adc(AnalogDigitalConverter::VoltageReference::AVCC,
                               AnalogDigitalConverter::ClockPrescaler::Eight,
                               AnalogDigitalConverter::TriggerMode::Auto);
    adc.startConversion();

    etl::string<8> result;

    while (true) {
        etl::to_string(adc.getResult(), result);
        usart << "ADC: " << result << ' ';

        _delay_ms(50);
    }

    return 0;
}