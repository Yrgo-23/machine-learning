/********************************************************************************
 * @brief Driver for the ATmega328P watchdog timer.
 ********************************************************************************/
#pragma once

#include "utils.h"

namespace driver 
{
namespace watchdog 
{
/********************************************************************************
 * @brief Enumeration class for selecting the timeout of the watchdog timer.
 ********************************************************************************/
enum class Timeout 
{
    Timeout16ms = 0,                                         // 16 ms
	Timeout32ms = (1 << WDP0),                               // 32 ms
	Timeout64ms = (1 << WDP1),                               // 64 ms
	Timeout128ms = (1 << WDP1) | (1 << WDP0),                // 128 ms
	Timeout256ms = (1 << WDP2),                              // 256 ms
	Timeout512ms = (1 << WDP2) | (1 << WDP0),                // 512 ms
	Timeout1024ms = (1 << WDP2) | (1 << WDP1),               // 1024 ms
	Timeout2048ms = (1 << WDP2) | (1 << WDP1) | (1 << WDP0), // 2048 ms
	Timeout4096ms = (1 << WDP3),                             // 4096 ms
	Timeout8192ms = (1 << WDP3) | (1 << WDP0)                // 8192 ms
};

/********************************************************************************
 * @brief Initializes the watchdog timer and sets the selected timeout.
 *
 * @param timeout The timeout of the watchdog timer.
 ********************************************************************************/
void init(const enum Timeout timeout);

/********************************************************************************
 * @brief Resets the watchdog timer. This function must be called before the
 *        watchdog timer elapses, else the system will be reset (or a watchdog
 *        interrupt will be generated, depending on the selected mode of the
 *        watchdog timer).
 ********************************************************************************/
void reset(void);

/********************************************************************************
 * @brief Enables system reset so that the system will be reset if the watchdog
 *        timer elapses, which occurs if the watchdog timer isn't reset in time.
 ********************************************************************************/
void enableSystemReset(void);

/********************************************************************************
 * @brief Disables system reset so that the system won't be reset even if the
 *        watchdog timer elapses.
 ********************************************************************************/
void disableSystemReset(void);

/********************************************************************************
 * @brief Enables watchdog timer interrupt so that an interrupt will occur if
 *        the watchdog timer elapses, which occurs if isn't reset in time.
 *
 * @param callback Function pointer to the callback routine to call when 
 *        the watchdog timer elapses.
 * 
 * @return True if Watchdog interrupt was enabled, else false.
 ********************************************************************************/
bool enableInterrupt(void (*callback)(void));

/********************************************************************************
 * @brief Disables watchdog timer interrupt so that no interrupt will occur
 *        if the watchdog timer elapses.
 ********************************************************************************/
void disableInterrupt(void);

} // namespace watchdog
} // namespace driver
