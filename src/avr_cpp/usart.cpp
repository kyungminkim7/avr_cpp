#include <avr_cpp/usart.h>

#include <avr/io.h>
#include <util/setbaud.h>

namespace avr {
namespace usart {

void init() {
    // Set baud rate
    UBRR0H = UBRRH_VALUE;
    UBRR0L = UBRRL_VALUE;

#if USE_2X
    UCSR0A |= (1 << U2X0);
#else
    UCSR0A &= ~(1 << U2X0);
#endif

    // Enable transmitter & receiver
    UCSR0B = (1 << TXEN0) | (1 << RXEN0);

    // Set 8-bit frame size & 1 stop bit
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

} // namespace usart
} // namespace avr
