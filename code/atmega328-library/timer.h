/********************************************************************************
 * @brief Driver for ATmega328P hardware timers. 
 *
 * @note Three hardware timers Timer 0 - Timer 2 are available.
 ********************************************************************************/
#pragma once

#include "utils.h"

namespace driver 
{

/********************************************************************************
 * @brief Class for hardware timer driver.
 ********************************************************************************/
class Timer
{
  public:

	/********************************************************************************
	 * @brief Enumeration class for selecting which timer circuit 0 - 2 to use.
	 ********************************************************************************/
    enum class Circuit 
    { 
        Timer0, 
	    Timer1, 
		Timer2  
	};

	/********************************************************************************
	 * @brief Default constructor, creates uninitialized timer.
	 ********************************************************************************/
    Timer() = default;

	/********************************************************************************
	 * @brief Creates new timer with specified elapse time if the selected circuit
	 *        isn't already reserved.
	 *
	 * @param circuit
	 *        The selected timer circuit (Timer 0 - Timer 2).
	 * @param elapseTimeMs
	 *        The elapse time of the timer in ms.
	 * @param startTimer
	 *        Indicates if the timer is to be started immediately after
	 *        initialization (default = false, i.e. timer not started). 
	 ********************************************************************************/
	Timer(const Circuit circuit, 
          const uint16_t elapseTimeMs, 
          const bool startTimer = false);

    /********************************************************************************
	 * @brief Deletes timer.
	 ********************************************************************************/
	~Timer();

	/********************************************************************************
	 * @brief Copy constructor deleted.
	 ********************************************************************************/
	Timer(Timer&) = delete;

	/********************************************************************************
	 * @brief Assignment operator deleted.
	 ********************************************************************************/
	Timer& operator=(Timer&) = delete;

	/********************************************************************************
	 * @brief Move constructor deleted.
	 ********************************************************************************/
	Timer(Timer&&) = delete;

	/********************************************************************************
	 * @brief Provides which timer circuit (Timer 0 - Timer 2) is used for the timer.
	 *
	 * @return The timer circuit used as an enumerator of enumeration class Circuit.
	 ********************************************************************************/
	Circuit circuit() const;

	/********************************************************************************
	 * @brief Indicated if the timer is enabled.
	 *
	 * @return True if the timer is enabled, else false.
	 ********************************************************************************/
	bool isEnabled() const;

    /********************************************************************************
	 * @brief Sets the timer state (enabled or disabled).
     *
     * @param enabled The new timer state (true = enabled, false = disabled).
	 ********************************************************************************/
    void setEnabled(const bool enabled);

    /********************************************************************************
	 * @brief Starts new elapse time of timer.
	 *
	 * @param elapseTimeMs The new elapse time measured in milliseconds.
	 ********************************************************************************/
	void setElapseTimeMs(const uint16_t elapseTimeMs);

    /********************************************************************************
	 * @brief Provides the elapse time of the timer.
	 *
	 * @return The elapse time of the timer measured in milliseconds.
	 ********************************************************************************/
	uint32_t elapseTimeMs() const;

	/********************************************************************************
	 * @brief Initializes timer with specified elapse time if the selected circuit
	 *        isn't already reserved.
	 *
	 * @param circuit      The selected timer circuit (Timer 0 - Timer 2).
	 * @param elapseTimeMs The elapse time of the timer in ms.
	 * @param startTimer   Indicates if the timer is to be started immediately after
	 *                     initialization (default = false, i.e. timer not started).
	 * 
	 * @return True upon successful initialization, else false. 
	 ********************************************************************************/
	bool init(const Circuit circuit, 
              const uint16_t elapseTimeMs, 
              const bool startTimer = false);

	/********************************************************************************
	 * @brief Starts timer.
	 ********************************************************************************/
	void start();

	/********************************************************************************
	 * @brief Stops timer.
	 ********************************************************************************/
	void stop();

	/********************************************************************************
	 * @brief Toggles timer.
	 ********************************************************************************/
	void toggle();

    /********************************************************************************
	 * @brief Restarts timer.
	 ********************************************************************************/
     void restart();

	/********************************************************************************
	 * @brief Adds callback for timer.
	 *
	 * @param callback Function pointer to specified callback.
	 *
	 * @return True if the callback was added, false if a nullptr was passed.
	 ********************************************************************************/
	bool addCallback(void (*callback)()) const;

	/********************************************************************************
	 * @brief Removes callback for timer.
	 ********************************************************************************/
	bool removeCallback() const;

    /********************************************************************************
	 * @brief Increments the timer if it's enabled.
     *
     * @return True if the timer was incremented, else false.
	 ********************************************************************************/
    bool increment();

    /********************************************************************************
	 * @brief Indicates if the timer has elapsed.
     *
     * @return True if the counter has elapsed, else false.
	 ********************************************************************************/
    bool hasElapsed();

  private:

    struct Hardware 
	{
	    volatile uint32_t counter;
	    volatile uint8_t* const maskReg;
	    const uint8_t maskBit;
		const uint8_t index;
    };

	bool initHardware();
	void disableHardware();
	static uint32_t getMaxCount(const uint16_t elapseTimeMs);

	static constexpr uint16_t Timer1MaxCount{256};
	static constexpr double InterruptPeriodMs{0.128};
    static Hardware myHwTimer0, myHwTimer1, myHwTimer2;

    Hardware* myHardware{nullptr};
    Circuit myCircuit{};
    uint32_t myMaxCount{};
    bool myEnabled{};
};

} // namespace driver
