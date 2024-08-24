/********************************************************************************
 * @brief Demonstration of GPIO device drivers in C++.
 ********************************************************************************/
#include "gpio.h"
#include "timer.h"
#include "watchdog.h"

using namespace driver;

namespace 
{

/********************************************************************************
 * @brief Devices used in the embedded system.
 *
 * @param led1    LED connected to pin 9, blinking every 100 ms when enabled.
 * @param button1 Button connected to pin 13, used to toggle the LED.
 * @param timer0  Timer used to reduced the effect of contact bounces when
 *                pressing the button.
 * @param timer1  Timer used to toggle the LED every 100 ms when enabled.
 ********************************************************************************/
GPIO led1{9, GPIO::Direction::Output};
GPIO button1{13, GPIO::Direction::InputPullup};
Timer timer0{Timer::Circuit::Timer0, 300};
Timer timer1{Timer::Circuit::Timer1, 100};

/********************************************************************************
 * @brief Callback routine called when button1 is pressed or released.
 *        Every time button1 is pressed, timer1 is toggled, which indirectly
 *        toggles the LED (since timer1 is responsible for toggling led1).
 *        Pin change interrupts are disabled for 300 ms on the button's I/O port
 *        to reduce the effects of contact bounces.
 ********************************************************************************/
void buttonCallback(void) 
{
    button1.disableInterruptsOnIoPort();
    timer0.start();

    if (button1.read()) 
    {
        timer1.toggle();
        if (!timer1.isEnabled()) { led1.clear(); }
    }
}

/********************************************************************************
 * @brief Enables pin change interrupts on the button's I/O port 300 ms after
 *        press or release to reduce the effects of contact bounces.
 ********************************************************************************/
void timer0Callback(void) 
{
    timer0.stop();
    button1.enableInterruptsOnIoPort();
}

/********************************************************************************
 * @brief Toggles led1 when timer1 elapses, which is every 100 ms when enabled.
 ********************************************************************************/
void timer1Callback(void) 
{
    led1.toggle();
}

/********************************************************************************
 * @brief Sets callback routines, enabled pin change interrupt on button1 and
 *        enables the watchdog timer in system reset mode.
 ********************************************************************************/
inline void setup(void) 
{
    button1.addCallback(buttonCallback);
    timer0.addCallback(timer0Callback);
    timer1.addCallback(timer1Callback);

    button1.enableInterrupt();
    watchdog::init(watchdog::Timeout::Timeout1024ms);
    watchdog::enableSystemReset();
}

} // namespace

/********************************************************************************
 * @brief Perform a setup of the system, then running the program as long as
 *        voltage is supplied. The hardware is interrupt controlled, hence the
 *        while loop is almost empty. If the program gets stuck anywhere, the
 *        watchdog timer won't be reset in time and the program will then restart.
 ********************************************************************************/
int main(void)
{
    setup();

    while (1) 
    {
        watchdog::reset();
    }
    return 0;
}

