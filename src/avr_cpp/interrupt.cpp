#include <avr_cpp/interrupt.h>

#include <avr/interrupt.h>

namespace avr_cpp {

void enableInterrupts() {
    sei();
}

void disableInterrupts() {
    cli();
}

} // namespace avr_cpp