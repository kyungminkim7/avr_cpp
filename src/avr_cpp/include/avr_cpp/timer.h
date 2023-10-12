#pragma once

#include <stdint.h>

#include "chrono.h"
#include "interrupt.h"
#include "ratio.h"

namespace avr_cpp {

namespace Timer {

enum class Mode { Repeat, SingleShot };
enum class PinMode { Toggle, Clear, Set };

} // namespace Timer

template<unsigned int PRESCALER>
class HighResolutionTimer {
    static_assert(PRESCALER == 1 ||
                  PRESCALER == 8 ||
                  PRESCALER == 64 ||
                  PRESCALER == 256 ||
                  PRESCALER == 1024,
                  "Clock prescaler must be either 1, 8, 64, 256, or 1024");
public:
    using duration = Chrono::Duration<uint16_t, 
                                      Ratio<PRESCALER, Chrono::SystemClock::frequency>>;
    static constexpr auto prescaler = PRESCALER;

    HighResolutionTimer();
    HighResolutionTimer(const duration &period, Timer::PinMode pinMode, Timer::Mode mode);
    HighResolutionTimer(const duration &period, 
                        InterruptServiceRoutine interruptServiceRoutine, 
                        Timer::Mode mode);

    ~HighResolutionTimer();

    void start();
    void reset();
    void stop();

    duration elapsedTime() const;

private:
    static void setNormalWaveformGenerationMode();
    static void setClearTimerOnCompareMatchWaveformGenerationMode();
    static void disableTimerInterrupts();
    static void setPeriod(const duration &period, Timer::Mode mode);
    static void setPinMode(Timer::PinMode pinMode, Timer::Mode mode);
    static void disconnectOutputComparePins(Timer::Mode mode);
    static void enableOutputCompareInterrupt(Timer::Mode mode);
    static void setOutputCompareInterruptServiceRoutine(InterruptServiceRoutine interruptServiceRoutine, 
                                                        Timer::Mode mode);
};

using HighResolutionTimer1 = HighResolutionTimer<1>;
using HighResolutionTimer8 = HighResolutionTimer<8>;
using HighResolutionTimer64 = HighResolutionTimer<64>;
using HighResolutionTimer256 = HighResolutionTimer<256>;
using HighResolutionTimer1024 = HighResolutionTimer<1024>;

} // namespace avr_cpp
