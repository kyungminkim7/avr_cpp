#include <avr/io.h>

#include <avr_cpp/digital_pin_bank.h>
#include <avr_cpp/usart0.h>


using namespace avr_cpp;

int main() {
    DigitalPinBank<> pins(DDRB, PORTB);
    pins.configureOutputPins(0, 1, 2);

    Usart0 usart(Usart::DataSize::eightBits,
                 Usart::NumStopBits::one, 9600);

    pins.writePin(0, true);
    // pins.writePin(1, true);
    pins.writePin(2, true);


    while (true) {
        usart.sendByte('H');
        usart.sendByte('e');
        usart.sendByte('l');
        usart.sendByte('l');
        usart.sendByte('o');
        usart.sendByte(' ');
    }

    return 0;
}
