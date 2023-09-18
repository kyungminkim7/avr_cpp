#include <avr/io.h>
#include <util/delay.h>

#include <avr_cpp/port.h>
#include <avr_cpp/usart0.h>

#include <etl/string.h>
#include <etl/vector.h>

using namespace avr_cpp;

int main() {
    Port<> port(DDRB, PINB, PORTB);
    port.configureOutputPins(0, 1, 2);

    Usart0 usart(Usart::DataSize::EightBits,
                 Usart::NumStopBits::One, 9600);

    port.setOutputPinsHigh(0, 1);

    while (true) {
        usart.send(0x48);
        usart.send("Hello ");
        usart.send(etl::make_string("World\n"));
        _delay_ms(500);
    }

    return 0;
}