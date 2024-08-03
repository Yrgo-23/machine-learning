/********************************************************************************
 * @brief Implementation details for the GPIO device driver.
 ********************************************************************************/
#include "callback_array.h"
#include "gpio.h"

namespace driver 
{

struct CallbackIndex
{
    static constexpr uint8_t PortB{0};
    static constexpr uint8_t PortC{1};
    static constexpr uint8_t PortD{2};
};

namespace
{

constexpr uint8_t NumIoPorts{3}; 
container::CallbackArray<NumIoPorts> callbacks{};

} // namespace

GPIO::Hardware GPIO::myHwPinB 
{
    .dirReg = &DDRB,
    .portReg = &PORTB,
    .pinReg = &PINB,
    .pcmskReg = &PCMSK0,
    .pcicrBit = PCIE0,
    .io_port = IoPort::B
};

GPIO::Hardware GPIO::myHwPinC 
{
	.dirReg = &DDRC,
	.portReg = &PORTC,
	.pinReg = &PINC,
	.pcmskReg = &PCMSK1,
	.pcicrBit = PCIE1,
    .io_port = IoPort::C
};

GPIO::Hardware GPIO::myHwPinD 
{
	.dirReg = &DDRD,
	.portReg = &PORTD,
	.pinReg = &PIND,
	.pcmskReg = &PCMSK2,
	.pcicrBit = PCIE2,
    .io_port = IoPort::D
};

uint32_t GPIO::myRegisteredPins{};

// -----------------------------------------------------------------------------
GPIO::GPIO() = default;

// -----------------------------------------------------------------------------
GPIO::GPIO(const uint8_t pin, const Direction direction) { init(pin, direction); }

// -----------------------------------------------------------------------------
GPIO::~GPIO()  { disable(); }

// -----------------------------------------------------------------------------
uint8_t GPIO::operator()() { return myPin; }

// -----------------------------------------------------------------------------
GPIO::IoPort GPIO::ioPort() const { return myHardware->io_port; };

// -----------------------------------------------------------------------------
bool GPIO::init(const uint8_t pin, const Direction direction)
{
    if (!isPinNumberValid(pin) || isPinReserved(pin)) { return false; }
    setIoRegPointers(pin);
    setDirection(direction);
    utils::set(myRegisteredPins, pin);
    return true;
}

// -----------------------------------------------------------------------------
void GPIO::disable()
{
    utils::clear(*(myHardware->dirReg), myPin);
    utils::clear(*(myHardware->portReg), myPin);
    utils::clear(myRegisteredPins, myPin);
    disableInterrupt();
    myHardware = nullptr;
    myPin = 0;
}

// -----------------------------------------------------------------------------
void GPIO::disableInterrupt() 
{ 
    utils::clear(*(myHardware->pcmskReg), myPin); 
}

// -----------------------------------------------------------------------------
void GPIO::enableInterruptsOnIoPort() 
{ 
    enableInterruptsOnIoPort(ioPort()); 
}

// -----------------------------------------------------------------------------
void GPIO::disableInterruptsOnIoPort() 
{ 
    disableInterruptsOnIoPort(ioPort());
}

// -----------------------------------------------------------------------------
bool GPIO::isInterruptEnabled() const 
{ 
    return utils::read(*(myHardware->pcmskReg), myPin); 
}

// -----------------------------------------------------------------------------
void GPIO::enableInterrupt() 
{
	utils::globalInterruptEnable();
	utils::set(PCICR, myHardware->pcicrBit);
	utils::set(*(myHardware->pcmskReg), myPin);
}

// -----------------------------------------------------------------------------
void GPIO::toggleInterrupt() 
{
	if (isInterruptEnabled()) { disableInterrupt(); }
    else { enableInterrupt(); }
}

// -----------------------------------------------------------------------------
void GPIO::set() 
{
	if (utils::read(*(myHardware->dirReg), myPin)) 
    {
		utils::set(*(myHardware->portReg), myPin);
	}
}

// -----------------------------------------------------------------------------
void GPIO::clear() 
{
	if (utils::read(*(myHardware->dirReg), myPin)) 
    {
		utils::clear(*(myHardware->portReg), myPin);
	}
}

// -----------------------------------------------------------------------------
void GPIO::toggle() 
{
	if (utils::read(*(myHardware->dirReg), myPin)) 
    {
		utils::set(*(myHardware->pinReg), myPin);
	}
}

// -----------------------------------------------------------------------------
bool GPIO::read() const 
{ 
    return utils::read(*(myHardware->pinReg), myPin); 
}

// -----------------------------------------------------------------------------
void GPIO::write(const uint8_t val) 
{
	if (val) { set(); }
	else { clear(); }
}

// -----------------------------------------------------------------------------
void GPIO::blink(const uint16_t& blinkSpeedMs) 
{
	toggle();
	utils::delayMs(blinkSpeedMs);
}

// -----------------------------------------------------------------------------
bool GPIO::addCallback(void (*callback)()) const
{
	if (myHardware->portReg == &PORTB) 
    {
        return callbacks.add(callback, CallbackIndex::PortB);
	} 
    else if (myHardware->portReg == &PORTC) 
    {
	    return callbacks.add(callback, CallbackIndex::PortC);
	} 
    else if (myHardware->portReg == &PORTD) 
    {
	    return callbacks.add(callback, CallbackIndex::PortD);
	}
    else
    {
        return false;
    }
}

// -----------------------------------------------------------------------------
void GPIO::removeCallback() const
{
    if (myHardware->portReg == &PORTB)
    {
        callbacks.remove(CallbackIndex::PortB);
    }
    else if (myHardware->portReg == &PORTC)
    {
        callbacks.remove(CallbackIndex::PortC);
    }
    else if (myHardware->portReg == &PORTD)
    {
        callbacks.remove(CallbackIndex::PortD);
    }
}

// -----------------------------------------------------------------------------
void GPIO::enableInterruptsOnIoPort(const IoPort io_port) 
{ 
    utils::globalInterruptEnable();
    utils::set(PCICR, static_cast<uint8_t>(io_port));
}

// -----------------------------------------------------------------------------
void GPIO::disableInterruptsOnIoPort(const IoPort io_port) 
{  
    utils::clear(PCICR, static_cast<uint8_t>(io_port));
}

// -----------------------------------------------------------------------------
void GPIO::setIoRegPointers(const uint8_t pin)  
{
	if (isPinConnectedToPortD(pin)) 
    {
		myHardware = &myHwPinD;
		myPin = pin;
	} 
    else if (isPinConnectedToPortB(pin)) 
    {
		myHardware = &myHwPinB;
		myPin = pin - 8;
	} 
    else if (isPinConnectedToPortC(pin)) 
    {
		myHardware = &myHwPinD;
		myPin = pin - 14;
	}
}

// -----------------------------------------------------------------------------
void GPIO::setDirection(const Direction direction)  
{
	if (direction == Direction::InputPullup) 
    {
		utils::set(*(myHardware->portReg), myPin);
	} 
    else if (direction == Direction::Output) 
    {
		utils::set(*(myHardware->dirReg), myPin);
	}
}

// -----------------------------------------------------------------------------
ISR (PCINT0_vect) 
{
    callbacks.call(CallbackIndex::PortB);
}

// -----------------------------------------------------------------------------
ISR (PCINT1_vect) 
{
    callbacks.call(CallbackIndex::PortC);
}

// -----------------------------------------------------------------------------
ISR (PCINT2_vect) 
{
    callbacks.call(CallbackIndex::PortD);
}

} // namespace driver
