/********************************************************************************
 * @brief Implementation details of the Raspberry Pi LED driver.
 ********************************************************************************/
#include <gpiod.h>

#include "gpiod_utils.h"
#include "led.h"

namespace rpi 
{

// -----------------------------------------------------------------------------
Led::Led(const std::uint8_t pin, const bool startValue) noexcept
    : myLine{gpiod_line_new(pin, GPIOD_LINE_DIRECTION_OUT)} 
{ 
    write(startValue); 
}

// -----------------------------------------------------------------------------
Led::~Led() noexcept { gpiod_line_release(myLine); }

// -----------------------------------------------------------------------------
std::uint8_t Led::pin() const noexcept { return ::gpiod_line_offset(myLine); }

// -----------------------------------------------------------------------------
bool Led::isEnabled() const noexcept { return gpiod_line_get_value(myLine) > 0; }

// -----------------------------------------------------------------------------
void Led::write(const bool value) noexcept
{
    gpiod_line_set_value(myLine, static_cast<int>(value));
}

// -----------------------------------------------------------------------------
void Led::toggle() noexcept { gpiod_line_set_value(myLine, !isEnabled()); }

// -----------------------------------------------------------------------------
void Led::blink(const std::uint16_t blinkSpeedMs) noexcept
{
    gpiod_line_blink(myLine, blinkSpeedMs);
}

} // namespace rpi