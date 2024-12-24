/********************************************************************************
 * @brief Implementation details of the Raspberry Pi button driver.
 ********************************************************************************/
#include <gpiod.h>

#include "gpiod_utils.h"
#include "button.h"

namespace rpi
{
    
// -----------------------------------------------------------------------------
Button::Button(const std::uint8_t pin, const bool activeHigh) noexcept
    : myLine{gpiod_line_new(pin, GPIOD_LINE_DIRECTION_IN)}
    , myActiveHigh{activeHigh}
    , myLastInput{!myActiveHigh} {}

// -----------------------------------------------------------------------------
Button::~Button() noexcept { gpiod_line_release(myLine); }

// -----------------------------------------------------------------------------
std::uint8_t Button::pin() const noexcept { return gpiod_line_offset(myLine); }

// -----------------------------------------------------------------------------
bool Button::isPressed() noexcept
{ 
    myLastInput = gpiod_line_get_value(myLine);
    return myActiveHigh ? myLastInput : !myLastInput;
}

// -----------------------------------------------------------------------------
bool Button::isEventDetected(const Edge edge) noexcept
{
    return gpiod_line_event_detected(myLine, static_cast<gpiod_line_edge>(edge), &myLastInput);
}

} // namespace rpi