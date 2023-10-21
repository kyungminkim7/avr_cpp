#include <avr_cpp/timer.h>

#include <avr/io.h>
#include <avr/interrupt.h>

#include <avr_cpp/bit.h>

namespace {

using namespace avr_cpp;

InterruptServiceRoutine highResolutionTimerCompareMatchInterruptServiceRoutineA;
InterruptServiceRoutine highResolutionTimerCompareMatchInterruptServiceRoutineB;

} // namespace

ISR(TIMER1_COMPA_vect) {
    highResolutionTimerCompareMatchInterruptServiceRoutineA();
}

ISR(TIMER1_COMPB_vect) {
    highResolutionTimerCompareMatchInterruptServiceRoutineB();
}

namespace avr_cpp {

template<unsigned int PRESCALER>
HighResolutionTimer<PRESCALER>::HighResolutionTimer() {
    setNormalWaveformGenerationMode();
}

template<unsigned int PRESCALER>
HighResolutionTimer<PRESCALER>::HighResolutionTimer(const duration &period, 
                                                    Timer::PinMode pinMode, 
                                                    Timer::Mode mode) {
    setClearTimerOnCompareMatchWaveformGenerationMode();
    setPeriod(period, mode);

    setPinMode(pinMode, mode);
}

template<unsigned int PRESCALER>
HighResolutionTimer<PRESCALER>::HighResolutionTimer(const duration &period, 
                                                    InterruptServiceRoutine interruptServiceRoutine, 
                                                    Timer::Mode mode) {
    setClearTimerOnCompareMatchWaveformGenerationMode();
    setPeriod(period, mode);

    setOutputCompareInterruptServiceRoutine(interruptServiceRoutine, mode);
    enableOutputCompareInterrupt(mode);
}

template<unsigned int PRESCALER>
HighResolutionTimer<PRESCALER>::~HighResolutionTimer() {
    stop();
    disconnectOutputComparePins();
    disableTimerInterrupts();
}

template<unsigned int PRESCALER>
void HighResolutionTimer<PRESCALER>::setNormalWaveformGenerationMode() {
    unsetBits(TCCR1A, WGM11, WGM10);
    unsetBits(TCCR1B, WGM13, WGM12);
}

template<unsigned int PRESCALER>
void HighResolutionTimer<PRESCALER>::setClearTimerOnCompareMatchWaveformGenerationMode() {
    unsetBits(TCCR1A, WGM11, WGM10);
    setBits(TCCR1B, WGM12);
    unsetBits(TCCR1B, WGM13);
}

template<unsigned int PRESCALER>
void HighResolutionTimer<PRESCALER>::disableTimerInterrupts() {
    unsetBits(TIMSK1, ICIE1, OCIE1B, OCIE1A, TOIE1);
}

template<unsigned int PRESCALER>
void HighResolutionTimer<PRESCALER>::setPeriod(const duration &period, 
                                               Timer::Mode mode) {
    switch (mode) {
    case Timer::Mode::Repeat:
        OCR1A = period.count();
        break;
    
    case Timer::Mode::SingleShot:
        OCR1B = period.count();
        break;
    }
}

template<unsigned int PRESCALER>
void HighResolutionTimer<PRESCALER>::setPinMode(Timer::PinMode pinMode,
                                                Timer::Mode mode) {
    const auto com1 = mode == Timer::Mode::Repeat ? COM1A1 : COM1B1;
    const auto com0 = mode == Timer::Mode::Repeat ? COM1A0 : COM1B0;

    switch (pinMode) {
    case Timer::PinMode::Toggle:
        unsetBits(TCCR1A, com1);
        setBits(TCCR1A, com0);
        break;

    case Timer::PinMode::Clear:
        setBits(TCCR1A, com1);
        unsetBits(TCCR1A, com0);
        break;

    case Timer::PinMode::Set:
        setBits(TCCR1A, com1, com0);
        break;
    }
}

template<unsigned int PRESCALER>
void HighResolutionTimer<PRESCALER>::disconnectOutputComparePins() {
    unsetBits(TCCR1A, COM1A1, COM1A0, COM1B1, COM1B0);
}

template<unsigned int PRESCALER>
void HighResolutionTimer<PRESCALER>::enableOutputCompareInterrupt(Timer::Mode mode) {
    switch (mode) {
    case Timer::Mode::Repeat:
        setBits(TIMSK1, OCIE1A);
        break;

    case Timer::Mode::SingleShot:
        setBits(TIMSK1, OCIE1B);
        break;
    }
}

template<unsigned int PRESCALER>
void HighResolutionTimer<PRESCALER>::setOutputCompareInterruptServiceRoutine(InterruptServiceRoutine interruptServiceRoutine, 
                                                                             Timer::Mode mode) {
    switch (mode) {
    case Timer::Mode::Repeat:
        highResolutionTimerCompareMatchInterruptServiceRoutineA = interruptServiceRoutine;
        break;

    case Timer::Mode::SingleShot:
        highResolutionTimerCompareMatchInterruptServiceRoutineB = interruptServiceRoutine;
        break;
    }
}

template<unsigned int PRESCALER>
void HighResolutionTimer<PRESCALER>::start() {
    reset();

    switch (PRESCALER) {
    case 1:
        setBits(TCCR1B, CS10);
        unsetBits(TCCR1B, CS12, CS11);
        break;

    case 8:
        setBits(TCCR1B, CS11);
        unsetBits(TCCR1B, CS12, CS10);
        break;

    case 64:
        setBits(TCCR1B, CS11, CS10);
        unsetBits(TCCR1B, CS12);
        break;

    case 256:
        setBits(TCCR1B, CS12);
        unsetBits(TCCR1B, CS11, CS10);
        break;

    case 1024:
        setBits(TCCR1B, CS12, CS10);
        unsetBits(TCCR1B, CS11);
        break;
    
    default:
        break;
    }
}

template<unsigned int PRESCALER>
void HighResolutionTimer<PRESCALER>::reset() {
    TCNT1 = 0;
}

template<unsigned int PRESCALER>
void HighResolutionTimer<PRESCALER>::stop() {
    unsetBits(TCCR1B, CS12, CS11, CS10);
}

template<unsigned int PRESCALER>
typename HighResolutionTimer<PRESCALER>::duration HighResolutionTimer<PRESCALER>::elapsedTime() const {
    return duration(TCNT1);
}

template class HighResolutionTimer<1>;
template class HighResolutionTimer<8>;
template class HighResolutionTimer<64>;
template class HighResolutionTimer<256>;
template class HighResolutionTimer<1024>;

} // namespace avr_cpp
