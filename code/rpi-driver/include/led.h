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
 ********************************************************************************/
class Led 
{
public:

    /********************************************************************************
     * @brief Default destructor deleted.
     ********************************************************************************/
    Led() = delete;

    /********************************************************************************
     * @brief Creates new button connected to specified GPIO pin.
     * 
     * @param pin        Raspberry Pi GPIO pin the LED is connected to.
     * @param startValue Initial value of the LED (default = off).
     ********************************************************************************/
    Led(const std::uint8_t pin, const bool startValue = false);
    ~Led();

    /********************************************************************************
     * @brief Deletes LED and releases allocated hardware resources.
     ********************************************************************************/
    std::uint8_t pin() const;

     /********************************************************************************
     * @brief Indicates if the LED is enabled/on.
     * 
     * @return True if the LED is enabled, else false.
     ********************************************************************************/
    bool isEnabled() const;

    /********************************************************************************
     * @brief Writes output value to enable/disable the LED.
     * 
     * @param value The value to write.
     ********************************************************************************/
    void write(const bool value);

    /********************************************************************************
     * @brief Toggles the LED.
     ********************************************************************************/
    void toggle();

    /********************************************************************************
     * @brief Blinks the LED with specified blink speed.
     * 
     * @param blinkSpeedMs The blinking speed measured in milliseconds.
     ********************************************************************************/
    void blink(const std::uint16_t blinkSpeedMs);

private:
    struct gpiod_line* myLine;
};

} // namespace rpi