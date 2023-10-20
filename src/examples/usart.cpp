/*
This program is an example of using USART to send and receive serial data.
*/

#include <stdint.h>

#include <avr_cpp/usart.h>

using namespace avr_cpp;

constexpr auto BAUD_RATE = 9600;

int main() {
    Usart0 usart(Usart::DataSize::EightBits,
                 Usart::NumStopBits::One, 
                 BAUD_RATE);

    uint8_t input;

    while (true) {
        usart << "Enter a character: ";
        usart >> input;

        usart << "\nReceived: " << input << '\n';
    }

    return 0;
}