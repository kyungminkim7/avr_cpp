/*
This program is an example of using a timer to repeatedly get the elapsed time.
*/

#include <util/delay.h>

#include <etl/string.h>
#include <etl/to_string.h>

#include <avr_cpp/chrono.h>
#include <avr_cpp/timer.h>
#include <avr_cpp/usart.h>

using namespace avr_cpp;

constexpr auto BAUD_RATE = 9600;

int main() {
    Usart0 usart(Usart::DataSize::EightBits,
                 Usart::NumStopBits::One, 
                 BAUD_RATE);

    etl::string<8> timeStr;

    HighResolutionTimer<64> timer;
    timer.start();

    while (true) {
        timer.reset();
        _delay_ms(1275);

        Chrono::Microseconds elapsedTime = timer.elapsedTime();

        etl::to_string(elapsedTime.count(), timeStr);
        usart << "Elapsed time: " << timeStr << " usec\n";
    }

    return 0;
}