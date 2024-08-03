/********************************************************************************
 * @brief Driver for miscellaneous GPIO devices.
 ********************************************************************************/
#pragma once

#include "utils.h"

namespace driver 
{

/********************************************************************************
 * @brief Class for generic GPIO driver.
 ********************************************************************************/
class GPIO 
{
public:

    /********************************************************************************
	 * @brief Struct containing port names for each pin, where I/O port D consists
	 *        of pin 0 - 7, I/O port B consists of pin 8 - 13 and I/O port C consists
	 *        of pin 14 - 19. 
	 ********************************************************************************/
    struct Port 
    {
	    static constexpr uint8_t D0{0};  // PORTD0 = pin 0
		static constexpr uint8_t D1{1};  // PORTD1 = pin 1
		static constexpr uint8_t D2{2};  // PORTD2 = pin 2
		static constexpr uint8_t D3{3};  // PORTD3 = pin 3
		static constexpr uint8_t D4{4};  // PORTD4 = pin 4 
		static constexpr uint8_t D5{5};  // PORTD5 = pin 5
		static constexpr uint8_t D6{6};  // PORTD6 = pin 6
		static constexpr uint8_t D7{7};  // PORTD7 = pin 7

		static constexpr uint8_t B0{8};  // PORTB0 = pin 8
		static constexpr uint8_t B1{9};  // PORTB1 = pin 9
		static constexpr uint8_t B2{10}; // PORTB2 = pin 10
		static constexpr uint8_t B3{11}; // PORTB3 = pin 11
		static constexpr uint8_t B4{12}; // PORTB4 = pin 12
		static constexpr uint8_t B5{13}; // PORTB5 = pin 13

		static constexpr uint8_t C0{14}; // PORTC0 = pin 14
		static constexpr uint8_t C1{15}; // PORTC1 = pin 15
		static constexpr uint8_t C2{16}; // PORTC2 = pin 16
		static constexpr uint8_t C3{17}; // PORTC3 = pin 17
		static constexpr uint8_t C4{18}; // PORTC4 = pin 18
		static constexpr uint8_t C5{19}; // PORTC5 = pin 10
	};

    /********************************************************************************
	 * @brief Enumeration class for selection GPIO direction.
	 *
	 * @param Input       Input without internal pull-up resistor enabled (tri-state).
	 * @param InputPullup Input with internal pull-up resistor enabled.
	 * @param Output      Output.
	 ********************************************************************************/
    enum class Direction
    { 
        Input, 
        InputPullup, 
        Output 
    };

    /********************************************************************************
     * @brief Enumeration class for selecting I/O port.
     *
     * @param B I/O port B.
     * @param C I/O port C.
     * @param D I/O port D.
     ********************************************************************************/
     enum class IoPort 
     {
         B = PCIE0, 
         C = PCIE1, 
         D = PCIE2
     };

	/********************************************************************************
	 * @brief Creates uninitialized device.
	 ********************************************************************************/
    GPIO();

	/********************************************************************************
	 * @brief Initializes device with specified parameters.
	 *
	 * @param pin       The PIN number of the device, either ATmega328P port numbers
	 *                  or Arduino pin numbers.
	 * @param direction The direction of the device.
	 ********************************************************************************/
	GPIO(const uint8_t pin, const Direction direction);

	/********************************************************************************
	 * @brief Copy constructor deleted.
	 ********************************************************************************/
	GPIO(GPIO&) = delete;

	/********************************************************************************
	 * @brief Assignment operator deleted.
	 ********************************************************************************/
	GPIO& operator=(GPIO&) = delete;

	/********************************************************************************
	 * @brief Move constructor deleted.
	 ********************************************************************************/
	GPIO(GPIO&&) = delete;

	/********************************************************************************
	 * @brief Disable device before deletion.
	 ********************************************************************************/
	~GPIO();

	/********************************************************************************
	 * @brief Provides the pin number of the device.
	 *
	 * @return The pin number of the device.
	 ********************************************************************************/
	uint8_t operator()();

	/********************************************************************************
	 * @brief Indicates if specified pin is reserved by an existing device.
	 *
	 * @return True if specified pin is reserved, else false.
	 ********************************************************************************/
	static constexpr bool isPinReserved(const uint8_t pin);

    /********************************************************************************
	 * @brief Provides the I/O port the device is connected to.
	 *
	 * @return The I/O port the device is connected to as an enumerator of the
     *         IoPort enum class.
	 ********************************************************************************/
     IoPort ioPort() const;

	/********************************************************************************
	 * @brief Initializes device with specified parameters.
	 *
	 * @param pin       The PIN number of the device, either ATmega328P
	 *                  port numbers or Arduino pin numbers.
	 * @param direction The direction of the device.
     *
	 * @return True if the initialization was successful, else false.
	 ********************************************************************************/
	bool init(const uint8_t pin, const Direction direction);

	/********************************************************************************
	 * @brief Disables device so that the pin can be used by another process.
	 ********************************************************************************/
	void disable();

	/********************************************************************************
	 * @brief Enables pin change interrupt for device.
	 ********************************************************************************/
	void enableInterrupt();

	/********************************************************************************
	 * @brief Disables pin change interrupt for device.
	 ********************************************************************************/
	void disableInterrupt();

    /********************************************************************************
     * @brief Enables pin change interrupts for entire I/O port the device is
     *        connected to.
     ********************************************************************************/
    void enableInterruptsOnIoPort();

    /********************************************************************************
     * @brief Disables pin change interrupts for entire I/O port the device is
     *        connected to.
     ********************************************************************************/
    void disableInterruptsOnIoPort();

	/********************************************************************************
	 * @brief Indicates if pin change interrupt is enabled for device.
	 *
	 * @return True if pin change interrupt is enabled, else false.
	 ********************************************************************************/
	bool isInterruptEnabled() const;

	/********************************************************************************
	 * @brief Toggles pin change interrupt for device.
	 ********************************************************************************/
	void toggleInterrupt();

	/********************************************************************************
	 * @brief Sets high output for device.
     *
	 * @note This operation is only permitted for pins set to output.
	 ********************************************************************************/
	void set();

	/********************************************************************************
	 * @brief Sets low output for device.
	 *        
	 * @note This operation is only permitted for pins set to output.
	 ********************************************************************************/
	void clear();

	/********************************************************************************
	 * @brief Toggles output for device.
	 *        
	 * @note This operation is only permitted for pins set to output.
	 ********************************************************************************/
	void toggle();

	/********************************************************************************
	 * @brief Reads input of device.
	 * 
	 * @return True if the input signal is high, else false.
	 ********************************************************************************/
	bool read() const;

	/********************************************************************************
	 * @brief Sets specified output of device.
	 *
	 * @note This operation is only permitted for pins set to output.
	 *
	 * @param val The output value to set (interpreted as 0 or 1).
	 ********************************************************************************/
	void write(const uint8_t val);

	/********************************************************************************
	 * @brief Blinks output of device with specified blink speed in ms.
	 *
	 * @note This operation is only permitted for pins set to output.
	 *
	 * @param blink_speed_ms The blink speed measured in milliseconds.
	 ********************************************************************************/
	void blink(const uint16_t& blink_speed_ms);

	/********************************************************************************
	 * @brief Add callback routine for device. 
     *
     * @note This callback is shared betweens all pins on the same port.
	 *
	 * @param callback Function pointer to the specified callback routine.
     *
     * @return True if the callback was added, else false.
	 ********************************************************************************/
	bool addCallback(void (*callback)()) const;

    /********************************************************************************
	 * @brief Removes callback set for device.
	 ********************************************************************************/
	void removeCallback() const;

    /********************************************************************************
     * @brief Enables pin change interrupts on the specified I/O port.
     *
     * @param io_port The I/O port to enable pin change interrupts on.
     ********************************************************************************/
    static void enableInterruptsOnIoPort(const IoPort io_port);

    /********************************************************************************
     * @brief Disables pin change interrupts on the specified I/O port.
     *
     * @param io_port The I/O port to disable pin change interrupts on.
     ********************************************************************************/
    static void disableInterruptsOnIoPort(const IoPort io_port);

  private:

    static constexpr uint8_t NumPins{20};
    static constexpr uint8_t PinMin{0};
	static constexpr uint8_t PinMax{NumPins - 1};

    /********************************************************************************
     * @note Provides access to hardware on an arbitrary I/O port.
     ********************************************************************************/
	struct Hardware 
    {
	    volatile uint8_t* const dirReg;
	    volatile uint8_t* const portReg;
	    volatile uint8_t* const pinReg;
	    volatile uint8_t* const pcmskReg;
		const uint8_t pcicrBit;
        const IoPort io_port;
	};

	static constexpr bool isPinNumberValid(const uint8_t pin);
	static constexpr bool isPinConnectedToPortB(const uint8_t pin);
	static constexpr bool isPinConnectedToPortC(const uint8_t pin);
	static constexpr bool isPinConnectedToPortD(const uint8_t pin);

	void setIoRegPointers(const uint8_t pin);
	void setDirection(const Direction direction);

    static Hardware myHwPinB, myHwPinC, myHwPinD;
    static uint32_t myRegisteredPins;
    Hardware* myHardware{nullptr};
    uint8_t myPin{};
    
};

// -----------------------------------------------------------------------------
constexpr bool GPIO::isPinReserved(const uint8_t pin)
{
    return pin <= PinMax ? utils::read(myRegisteredPins, pin) : false;
}

// -----------------------------------------------------------------------------
constexpr bool GPIO::isPinNumberValid(const uint8_t pin) 
{
    return pin <= PinMax;
}

// -----------------------------------------------------------------------------
constexpr bool GPIO::isPinConnectedToPortB(const uint8_t pin) 
{
    return pin >= Port::B0 && pin <= Port::B5;
}

// -----------------------------------------------------------------------------
constexpr bool GPIO::isPinConnectedToPortC(const uint8_t pin) 
{
    return pin >= Port::C0 && pin <= Port::C5;
}

// -----------------------------------------------------------------------------
constexpr bool GPIO::isPinConnectedToPortD(const uint8_t pin) 
{
    return pin >= Port::D0 && pin <= Port::D7;
}

} // namespace driver