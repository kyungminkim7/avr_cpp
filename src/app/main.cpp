#include <avr/io.h>

#include <avr_cpp/port.h>
#include <avr_cpp/usart0.h>

using namespace avr_cpp;

struct MyStruct {
    int x = 0;
};

int main() {
    Port<> port(DDRB, PINB, PORTB);
    port.configureOutputPins(0, 1, 2);

    Usart0 usart(Usart::DataSize::eightBits,
                 Usart::NumStopBits::one, 9600);

    port.setOutputPinsHigh(0, 1);


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