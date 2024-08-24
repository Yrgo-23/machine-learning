#include "gpiod_utils.h"
#include "button.h"

namespace yrgo 
{
namespace rpi
{
// -----------------------------------------------------------------------------
Button::Button(const std::uint8_t pin, const bool activeHigh)
    : myLine{gpiod_line_new(pin, GPIOD_LINE_DIRECTION_IN)}
    , myActiveHigh{activeHigh}
    , myLastInput{!myActiveHigh} {}

// -----------------------------------------------------------------------------
Button::~Button() { gpiod_line_release(myLine); }

// -----------------------------------------------------------------------------
std::uint8_t Button::pin() const { return gpiod_line_offset(myLine); }

// -----------------------------------------------------------------------------
bool Button::isPressed() 
{ 
    myLastInput = gpiod_line_get_value(myLine);
    return myActiveHigh ? myLastInput : !myLastInput;
}

// -----------------------------------------------------------------------------
bool Button::isEventDetected(const Edge edge)
{
    return gpiod_line_event_detected(myLine, 
        static_cast<enum gpiod_line_edge>(edge), &myLastInput);
}

} // namespace rpi
} // namespace yrgo