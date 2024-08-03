/********************************************************************************
 * @brief Implementation details for the ATmega328P watchdog timer driver.
 ********************************************************************************/
#include "watchdog.h"

namespace driver 
{
namespace watchdog 
{
namespace 
{

void (*watchdogCallback)(void){nullptr};

// -----------------------------------------------------------------------------
inline void resetWatchdogInHardware(void) { asm("WDR"); }

// -----------------------------------------------------------------------------
inline void clearWatchdogResetFlag(void) { utils::clear(MCUSR, WDRF); }

} // namespace

// -----------------------------------------------------------------------------
void init(const enum Timeout timeout) 
{
    utils::globalInterruptDisable();
	utils::set(WDTCSR, WDCE, WDE);
	WDTCSR = static_cast<uint8_t>(timeout);
	utils::globalInterruptEnable();
}

// -----------------------------------------------------------------------------
void reset(void) 
{
    utils::globalInterruptDisable();
	resetWatchdogInHardware();
	clearWatchdogResetFlag();
	utils::globalInterruptEnable();
}

// -----------------------------------------------------------------------------
void enableSystemReset(void) 
{
    reset();
	utils::globalInterruptDisable();
	utils::set(WDTCSR, WDCE, WDE);
	utils::set(WDTCSR, WDE);
	utils::globalInterruptEnable();
}

// -----------------------------------------------------------------------------
void disableSystemReset(void) 
{
    reset();
    utils::globalInterruptDisable();
    utils::set(WDTCSR, WDCE, WDE);
    utils::clear(WDTCSR, WDE);
    utils::globalInterruptEnable();
}

// -----------------------------------------------------------------------------
bool enableInterrupt(void (*callback)(void)) 
{
   if (callback == nullptr) { return false; }
   watchdogCallback = callback;
   reset();
   utils::globalInterruptDisable();
   utils::set(WDTCSR, WDCE, WDE);
   utils::set(WDTCSR, WDIE);
   utils::globalInterruptEnable();
   return true;
}

// -----------------------------------------------------------------------------
void disableInterrupt(void) 
{
   reset();
   utils::globalInterruptDisable();
   utils::set(WDTCSR, WDCE, WDE);
   utils::clear(WDTCSR, WDIE);
   utils::globalInterruptEnable();
}

// -----------------------------------------------------------------------------
ISR (WDT_vect) 
{
    enableInterrupt(watchdogCallback);
    if (watchdogCallback != nullptr) { watchdogCallback(); }
}

} // namespace watchdog
} // namespace driver
