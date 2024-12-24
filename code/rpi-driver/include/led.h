/********************************************************************************
 * @brief Led driver for Raspberry Pi.
 ********************************************************************************/
#pragma once

#include <cstdint>

struct gpiod_line;

namespace rpi 
{

/********************************************************************************
 * @brief Implementation of Raspberry Pi LED driver.
 * 
 *        This class is non-copyable and non-movable.
 ********************************************************************************/
class Led 
{
public:

    /********************************************************************************
     * @brief Creates new LED connected to specified GPIO pin.
     * 
     * @param pin        Raspberry Pi GPIO pin the LED is connected to.
     * @param startValue Initial value of the LED (default = off).
     ********************************************************************************/
    Led(const std::uint8_t pin, const bool startValue = false) noexcept;

    /********************************************************************************
     * @brief Deletes LED and releases allocated hardware.
     ********************************************************************************/
    ~Led() noexcept;

    /********************************************************************************
     * @brief Provides the GPIO pin the LED is connected to.
     * 
     * @return The Raspberry Pi GPIO pin the LED is connected to.
     ********************************************************************************/
    std::uint8_t pin() const noexcept;

     /********************************************************************************
     * @brief Indicates if the LED is enabled/on.
     * 
     * @return True if the LED is enabled, else false.
     ********************************************************************************/
    bool isEnabled() const noexcept;

    /********************************************************************************
     * @brief Writes output value to enable/disable the LED.
     * 
     * @param value The value to write.
     ********************************************************************************/
    void write(const bool value) noexcept;

    /********************************************************************************
     * @brief Toggles the LED.
     ********************************************************************************/
    void toggle() noexcept;

    /********************************************************************************
     * @brief Blinks the LED with specified blink speed.
     * 
     * @param blinkSpeedMs The blinking speed measured in milliseconds.
     ********************************************************************************/
    void blink(const std::uint16_t blinkSpeedMs) noexcept;

    Led()                      = delete; // No default constructor.
    Led(const Led&)            = delete; // No copy constructor.
    Led(Led&&)                 = delete; // No move constructor.
    Led& operator=(const Led&) = delete; // No copy assignment.
    Led& operator=(Led&&)      = delete; // No move assignment.

private:
    struct gpiod_line* myLine; // Pointer to GPIO line.
};

} // namespace rpi