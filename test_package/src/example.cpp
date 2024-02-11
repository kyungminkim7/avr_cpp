#include <stdint.h>

#include <avr/io.h>

#include <avr_cpp/bit.h>

using namespace avr_cpp;

int main() {
    constexpr auto PIN = 3;
    setBits(DDRB, PIN);
    setBits(PORTB, PIN);
    return 0;
}
