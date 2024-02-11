#include <gmock/gmock.h>

#include <avr/io.h>

#include <avr_cpp/chrono.h>
#include <avr_cpp/interrupt.h>
#include <avr_cpp/timer.h>
#include <avr_cpp_test/chrono.h>
#include <avr_cpp_test/matchers.h>

using namespace ::testing;
using namespace avr_cpp;

class TimerSetHighResolutionPrescaler : public Test {
public:
    TimerSetHighResolutionPrescaler() {
        TCCR1B = 0;
    }
};

TEST_F(TimerSetHighResolutionPrescaler, One) {
    HighResolutionTimer1_1 timer;
    timer.start();

    ASSERT_THAT(TCCR1B, BitsAreSet(CS10));
    ASSERT_THAT(TCCR1B, BitsAreUnset(CS12, CS11));
}

TEST_F(TimerSetHighResolutionPrescaler, Eight) {
    HighResolutionTimer1_8 timer;
    timer.start();

    ASSERT_THAT(TCCR1B, BitsAreSet(CS11));
    ASSERT_THAT(TCCR1B, BitsAreUnset(CS12, CS10));
}

TEST_F(TimerSetHighResolutionPrescaler, SixtyFour) {
    HighResolutionTimer1_64 timer;
    timer.start();

    ASSERT_THAT(TCCR1B, BitsAreSet(CS11, CS10));
    ASSERT_THAT(TCCR1B, BitsAreUnset(CS12));
}

TEST_F(TimerSetHighResolutionPrescaler, TwoHundredFiftySix) {
    HighResolutionTimer1_256 timer;
    timer.start();

    ASSERT_THAT(TCCR1B, BitsAreSet(CS12));
    ASSERT_THAT(TCCR1B, BitsAreUnset(CS11, CS10));
}

TEST_F(TimerSetHighResolutionPrescaler, OneThousandTwentyFour) {
    HighResolutionTimer1_1024 timer;
    timer.start();

    ASSERT_THAT(TCCR1B, BitsAreSet(CS12, CS10));
    ASSERT_THAT(TCCR1B, BitsAreUnset(CS11));
}

TEST(Timer, StartResetsCounterValue) {
    HighResolutionTimer1_1 timer;
    TCNT1 = 0xFFFF;

    timer.start();

    ASSERT_THAT(TCNT1, Eq(0));
}

TEST(Timer, ResetClearsCounterValue) {
    HighResolutionTimer1_8 timer;
    TCNT1 = 0xFFFF;

    timer.reset();

    ASSERT_THAT(TCNT1, Eq(0));
}

TEST(Timer, StopClearsClockSelectBits) {
    HighResolutionTimer1_1024 timer;
    timer.start();

    timer.stop();

    ASSERT_THAT(TCCR1B, BitsAreUnset(CS12, CS11, CS10));
}

TEST(Timer, ElapsedTimeConvertsTicksToDuration) {
    constexpr auto MICROSECONDS_PER_SEC = 1'000'000ul;
    using HiResTimer = HighResolutionTimer1_64;
    HiResTimer timer;

    constexpr auto TICKS = 17;
    TCNT1 = TICKS;

    ASSERT_THAT(timer.elapsedTime(), 
                Eq(Chrono::Microseconds(TICKS * HiResTimer::prescaler * 
                                        MICROSECONDS_PER_SEC / 
                                        Chrono::SystemClock::frequency)));
}

TEST(Timer, NormalModeSetsWaveformGenerationModeBits) {
    TCCR1A = 0xFF;
    TCCR1B = 0xFF;

    HighResolutionTimer1_8 timer;

    ASSERT_THAT(TCCR1A, BitsAreUnset(WGM11, WGM10));
    ASSERT_THAT(TCCR1B, BitsAreUnset(WGM13, WGM12));
}

class TimerPeriod : public Test {
public:
    static constexpr auto NUM_MILLISECONDS = 500;
    static constexpr auto PERIOD = Chrono::Milliseconds(NUM_MILLISECONDS);
};

TEST_F(TimerPeriod, SetsClearTimerOnCompareMatchWaveformGenerationMode) {
    TCCR1A = 0xFF;
    TCCR1B = 0;

    HighResolutionTimer1_64 timer(PERIOD, Timer::PinMode::Toggle, 
                                  Timer::Mode::Repeat);

    ASSERT_THAT(TCCR1A, BitsAreUnset(WGM11, WGM10));
    ASSERT_THAT(TCCR1B, BitsAreSet(WGM12));
    ASSERT_THAT(TCCR1B, BitsAreUnset(WGM13));
}

TEST_F(TimerPeriod, SetsOutputCompareRegister) {
    static constexpr auto MICROS_PER_MILLI = 1000;
    HighResolutionTimer1_64 timer(PERIOD, Timer::PinMode::Toggle, 
                                  Timer::Mode::SingleShot);

    ASSERT_THAT(OCR1B, Eq(NUM_MILLISECONDS * Chrono::SystemClock::frequency / 
                          HighResolutionTimer1_64::prescaler / MICROS_PER_MILLI));
}

class TimerSetPinMode : public Test {
public:
    using HiResTimer = HighResolutionTimer1_1024;

    static constexpr auto PERIOD = Chrono::Milliseconds(500);
    
    TimerSetPinMode() {
        TCCR1A = 0;
    }
};

TEST_F(TimerSetPinMode, Toggle) {
    HiResTimer timer(PERIOD, Timer::PinMode::Toggle, Timer::Mode::SingleShot);

    ASSERT_THAT(TCCR1A, BitsAreUnset(COM1B1));
    ASSERT_THAT(TCCR1A, BitsAreSet(COM1B0));
}

TEST_F(TimerSetPinMode, Clear) {
    HiResTimer timer(PERIOD, Timer::PinMode::Clear, Timer::Mode::Repeat);

    ASSERT_THAT(TCCR1A, BitsAreSet(COM1A1));
    ASSERT_THAT(TCCR1A, BitsAreUnset(COM1A0));
}

TEST_F(TimerSetPinMode, Set) {
    HiResTimer timer(PERIOD, Timer::PinMode::Set, Timer::Mode::Repeat);

    ASSERT_THAT(TCCR1A, BitsAreSet(COM1A1, COM1A0));
}

class TimerInterruptServiceRoutine : public Test {
public:
    using HiResTimer = HighResolutionTimer1_8;

    static constexpr auto PERIOD = Chrono::Milliseconds(500);
};

static void interruptServiceRoutine() {}

TEST_F(TimerInterruptServiceRoutine, enablesOutputCompareMatchInterrupt) {
    TIMSK1 = 0;

    HiResTimer timer(PERIOD, InterruptServiceRoutine::create<interruptServiceRoutine>(), 
                     Timer::Mode::SingleShot);

    ASSERT_THAT(TIMSK1, BitsAreSet(OCIE1B));
}

class TimerDestructor : public Test {
public:
    using HiResTimer = HighResolutionTimer1_1;

    TimerDestructor() {
        HiResTimer timer(HiResTimer::duration(40), 
                         InterruptServiceRoutine::create<interruptServiceRoutine>(),
                         Timer::Mode::SingleShot);
    }
};

TEST_F(TimerDestructor, StopsTimer) {
    ASSERT_THAT(TCCR1B, BitsAreUnset(CS12, CS11, CS10));
}

TEST_F(TimerDestructor, DisablesInterrupts) {
    ASSERT_THAT(TIMSK1, BitsAreUnset(ICIE1, OCIE1B, OCIE1A, TOIE1));
}

TEST_F(TimerDestructor, DisconnectsOutputComparePins) {
    {
        HiResTimer timer(HiResTimer::duration(40), 
                         Timer::PinMode::Toggle,
                         Timer::Mode::SingleShot);
    }
    ASSERT_THAT(TCCR1A, BitsAreUnset(COM1A1, COM1A0, COM1B1, COM1B0));
}
