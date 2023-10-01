#include <util/delay.h>

#include <etl/string.h>
#include <etl/to_string.h>

#include <avr_cpp/chrono.h>
#include <avr_cpp/usart0.h>

using namespace avr_cpp;

constexpr auto BAUD_RATE = 9600;

int main() {
    Usart0 usart(Usart::DataSize::EightBits,
                 Usart::NumStopBits::One, 
                 BAUD_RATE);

    Chrono::Seconds d1(4);
    Chrono::Minutes d2(2);

    etl::string<8> str;

    while (true) {
        d1 += d2;
        etl::to_string(d1.count(), str);
        usart << str << ' ';

        _delay_ms(1000);
    }

    return 0;
}