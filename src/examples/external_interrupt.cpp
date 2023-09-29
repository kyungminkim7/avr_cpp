/*
This program is an example of using external interrupts.

An external interrupt is used to detect button presses and releases
to turn an led on and off while the main loop repeatedly flashes another
led on and off.
*/

#include <avr/io.h>
#include <util/delay.h>

#include <etl/delegate.h>

#include <avr_cpp/interrupt.h>
#include <avr_cpp/external_interrupt.h>
#include <avr_cpp/port.h>

using namespace avr_cpp;

constexpr auto BUTTON = PD2;
constexpr auto FLASHING_LED = PB0;
constexpr auto LED = PB2;

auto inputPins = makePort(DDRD, PIND, PORTD);
auto leds = makePort(DDRB, PINB, PORTB);

void onButtonEvent() {
    if (inputPins.readInputPin(BUTTON)) {
        leds.setOutputPinsLow(LED);
    } else {
        leds.setOutputPinsHigh(LED);
    }
}

int main() {
    leds.configureOutputPins(FLASHING_LED, LED);

    inputPins.enableInputPinPullupResistors(BUTTON);
    ExternalInterrupt::set(INT0, ExternalInterrupt::Sense::Change,
                           InterruptServiceRoutine::create<onButtonEvent>());
    enableInterrupts();

    while (true) {
        leds.toggleOutputPins(FLASHING_LED);
        _delay_ms(1000);
    }

    return 0;
}