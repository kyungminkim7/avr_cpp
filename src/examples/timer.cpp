/*
This program is an example of using a hardware timer to periodically
call an interrupt service routine.
*/
#include <avr/io.h>
#include <util/delay.h>

#include <avr_cpp/chrono.h>
#include <avr_cpp/interrupt.h>
#include <avr_cpp/port.h>
#include <avr_cpp/timer.h>
#include <avr_cpp/usart0.h>

using namespace avr_cpp;

constexpr auto BAUD_RATE = 9600;
Usart0 usart(Usart::DataSize::EightBits,
             Usart::NumStopBits::One, 
             BAUD_RATE);

void sendMessage() {
    usart << "Timer message ";
}

int main() {
    auto leds = makePort(DDRB, PINB, PORTB);
    leds.configureOutputPins(PB0);

    using HiResTimer = HighResolutionTimer64;
    HiResTimer timer(Chrono::durationCast<HiResTimer::duration>(Chrono::Milliseconds(500)),
                     InterruptServiceRoutine::create<sendMessage>(),
                     Timer::Mode::Repeat);
    enableInterrupts();
    timer.start();

    while (true) {
        leds.toggleOutputPins(PB0);
        _delay_ms(1500);
    }

    return 0;
}