/*
This program is an example of setting servo positions to user-defined angles.
Min and max pulse widths are for a Hitec HS-422 servo determined through
the examples/servo_characterization program.
*/
#include <avr/io.h>
#include <etl/string.h>
#include <etl/to_arithmetic.h>

#include <avr_cpp/bit.h>
#include <avr_cpp/servo.h>
#include <avr_cpp/usart.h>

using namespace avr_cpp;

constexpr auto BAUD_RATE = 9600;
constexpr auto MIN_PULSE = Chrono::Microseconds(644);
constexpr auto MAX_PULSE = Chrono::Microseconds(2554);

int main() {
    Usart0 usart(Usart::DataSize::EightBits,
                 Usart::NumStopBits::One, 
                 BAUD_RATE);

    setBits(DDRB, PB1);
    Servo1 servo(Timer::Channel::A, MIN_PULSE, MAX_PULSE);
    servo.setPosition(0);

    etl::string<20> angleStr;

    while (true) {
        usart << "Enter servo position (degrees):";
        usart >> angleStr;
        usart << "\nSetting servo position: " << angleStr << " degrees\n";

        const float angle = etl::to_arithmetic<float>(angleStr);
        servo.setPosition(angle);
    }

    return 0;
}