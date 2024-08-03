/********************************************************************************
 * @brief Implementation details for the hardware timer driver.
 ********************************************************************************/
#include "array.h"
#include "callback_array.h"
#include "timer.h"

namespace driver 
{

struct ControlBits 
{
	static constexpr uint8_t Timer0{(1 << CS01)};
	static constexpr uint8_t Timer1{(1 << CS11) | (1 << WGM12)};
	static constexpr uint8_t Timer2{(1 << CS21)};
};

struct TimerIndex 
{
	static constexpr uint8_t Timer0{0};
	static constexpr uint8_t Timer1{1};
	static constexpr uint8_t Timer2{2};
};

namespace
{    
constexpr uint8_t kNumCircuits{3};
container::CallbackArray<kNumCircuits> callbacks{};
container::Array<Timer*, kNumCircuits> timers{};

// -----------------------------------------------------------------------------
void generateCallback(const uint8_t timerIndex)
{
    Timer* timer{timers[timerIndex]};
    if (timer != nullptr)
    {
        timer->increment();
        if (timer->hasElapsed())
        {
            callbacks.call(timerIndex);
        }
    }
}

} // namespace

// -----------------------------------------------------------------------------
Timer::Hardware Timer::myHwTimer0 
{
    .counter = 0,
    .maskReg = &TIMSK0,
    .maskBit = TOIE0,
    .index = TimerIndex::Timer0
};

// -----------------------------------------------------------------------------
Timer::Hardware Timer::myHwTimer1 
{
    .counter = 0,
	.maskReg = &TIMSK1,
    .maskBit = OCIE1A,
	.index = TimerIndex::Timer1
};

// -----------------------------------------------------------------------------
Timer::Hardware Timer::myHwTimer2 
{
    .counter = 0,
    .maskReg = &TIMSK2,
    .maskBit = TOIE2,
	.index = TimerIndex::Timer2
};

// -----------------------------------------------------------------------------
Timer::Timer(const Circuit circuit, 
             const uint16_t elapseTimeMs, 
             const bool startTimer) 
    : myCircuit{circuit} 
{
    if (!initHardware()) { return; }
	setElapseTimeMs(elapseTimeMs);
	if (startTimer) { start(); }
}

// -----------------------------------------------------------------------------
Timer::~Timer() { disableHardware(); }

// -----------------------------------------------------------------------------
Timer::Circuit Timer::circuit() const { return myCircuit; }

// -----------------------------------------------------------------------------
bool Timer::isEnabled() const { return myEnabled; }

// -----------------------------------------------------------------------------
void Timer::setEnabled(const bool enabled) 
{ 
    if (enabled) { start(); }
    else { stop(); }
}

// -----------------------------------------------------------------------------
uint32_t Timer::elapseTimeMs() const
{
    return static_cast<uint32_t>(myMaxCount * InterruptPeriodMs);
}

// -----------------------------------------------------------------------------
void Timer::setElapseTimeMs(const uint16_t elapseTimeMs)
{
    if (elapseTimeMs == 0) { stop(); }
    myMaxCount = getMaxCount(elapseTimeMs);
}

// -----------------------------------------------------------------------------
bool Timer::init(const Circuit circuit, 
                 const uint16_t elapseTimeMs, 
                 const bool startTimer) 
{
	myCircuit = circuit;
    if (!initHardware()) { return false; }
    setElapseTimeMs(elapseTimeMs);
    if (startTimer) { start(); }
    return true;
}

// -----------------------------------------------------------------------------
void Timer::start() 
{ 
    utils::globalInterruptEnable();

    if (myMaxCount > 0) 
    {
	    utils::set(*(myHardware->maskReg), myHardware->maskBit);
	    myEnabled = true;
	}
}

// -----------------------------------------------------------------------------
void Timer::stop() 
{ 
    utils::clear(*(myHardware->maskReg), myHardware->maskBit); 
	myEnabled = false; 
}

// -----------------------------------------------------------------------------
void Timer::toggle() { setEnabled(!myEnabled); }

// -----------------------------------------------------------------------------
void Timer::restart() 
{
    myHardware->counter = 0;
    start();
}

// -----------------------------------------------------------------------------
bool Timer::addCallback(void (*callback)()) const
 {
    if (callback) 
    {
        return callbacks.add(callback, myHardware->index);
	} 
    else 
    {
	    return false;
	}
}

// -----------------------------------------------------------------------------
bool Timer::removeCallback() const
{
    return callbacks.remove(myHardware->index);
}

// -----------------------------------------------------------------------------
bool Timer::increment()
{
    if (myEnabled) { myHardware->counter++; }
    return myEnabled;
}

// -----------------------------------------------------------------------------
bool Timer::hasElapsed() 
{
    if (!myEnabled || myHardware->counter < myMaxCount) 
	{
	    return false;
	} 
	else 
	{
	    myHardware->counter = 0;
		return true;
	}
}

// -----------------------------------------------------------------------------
bool Timer::initHardware() 
{
	if (myCircuit == Timer::Circuit::Timer0) 
	{
	    if (timers[TimerIndex::Timer0] != nullptr) { return false; }
	    TCCR0B = ControlBits::Timer0;
	    myHardware = &myHwTimer0;
	} 
	else if (myCircuit == Timer::Circuit::Timer1) 
	{
		if (timers[TimerIndex::Timer1] != nullptr) { return false; }
		TCCR1B = ControlBits::Timer1;
		OCR1A = Timer1MaxCount;
		myHardware = &myHwTimer1;
	} 
	else if (myCircuit == Timer::Circuit::Timer2) 
	{
		if (timers[TimerIndex::Timer2] != nullptr) { return false; }
		TCCR2B = ControlBits::Timer2;
		myHardware = &myHwTimer2;
	}
	timers[myHardware->index] = this;
	return true;
}

// -----------------------------------------------------------------------------
void Timer::disableHardware() 
{
	if (myCircuit == Timer::Circuit::Timer0) 
    {
		TCCR0B = 0x00;
	} 
	else if (myCircuit == Timer::Circuit::Timer1) 
	{
		TCCR1B = 0x00;
		OCR1A = 0x00;
	} 
	else if (myCircuit == Timer::Circuit::Timer2) 
	{
		TCCR2B = 0x00;
	}
    *(myHardware->maskReg) = 0x00;
	timers[myHardware->index] = nullptr;
	myHardware = nullptr;
}

// -----------------------------------------------------------------------------
uint32_t Timer::getMaxCount(const uint16_t elapseTimeMs) 
{
    return elapseTimeMs > 0 ? 
        utils::round<uint32_t>(elapseTimeMs / InterruptPeriodMs) : 0;
}

// -----------------------------------------------------------------------------
ISR (TIMER0_OVF_vect) 
{
    generateCallback(TimerIndex::Timer0);
}

// -----------------------------------------------------------------------------
ISR (TIMER1_COMPA_vect) 
{
    generateCallback(TimerIndex::Timer1);
}

// -----------------------------------------------------------------------------
ISR (TIMER2_OVF_vect) 
{
	generateCallback(TimerIndex::Timer2);
}

} // namespace driver
