#include <avr/io.h>

int main() {
    DDRB |= 1;

    PORTB = 1;

    return 0;
}
