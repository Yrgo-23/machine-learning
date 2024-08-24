/********************************************************************************
 * @brief Example program demonstrating the Raspberry Pi GPIO drivers.
 ********************************************************************************/
#include "button.h"
#include "led.h"

/********************************************************************************
 * @brief Toggles a LED connected to pin 17 at press of a button connected
 *        to pin 27.
 ********************************************************************************/
int main()
{
    rpi::Led led1{17};
    rpi::Button button1{27};
    
    while (1)
    {
        if (button1.isEventDetected())
        {
            led1.toggle();
        }
    }
    return 0;
}