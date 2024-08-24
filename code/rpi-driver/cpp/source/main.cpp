#include "button.h"
#include "led.h"

namespace rpi = yrgo::rpi;

/********************************************************************************
 * @brief Toggles a LED connected to pin 17 at pressdown of a button connected
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