/*
This program characterizes a servo by sending user-specified pulse widths.
This can assist in determining pulse width and angle position range limits.
*/
#include <avr/io.h>
#include <etl/string.h>
#include <etl/to_arithmetic.h>

#include <avr_cpp/bit.h>
#include <avr_cpp/servo.h>
#include <avr_cpp/usart.h>

using namespace avr_cpp;

constexpr auto BAUD_RATE = 9600;

int main() {
    setBits(DDRB, PB1);
    Servo1 servo(Timer::Channel::A);
    Usart0 usart(Usart::DataSize::EightBits,
                 Usart::NumStopBits::One, 
                 BAUD_RATE);

    etl::string<20> pulse;

    while (true) {
        usart << "Enter pulse (usec): ";
        usart >> pulse;
        usart << "\nSending servo pulse: " << pulse << " usec\n";

        OCR1A = etl::to_arithmetic<uint16_t>(pulse);
    }

    return 0;
}