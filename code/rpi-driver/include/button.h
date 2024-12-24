/********************************************************************************
 * @brief Button driver for Raspberry Pi.
 ********************************************************************************/
#pragma once

#include <cstdint>

struct gpiod_line;

namespace rpi
{

/********************************************************************************
 * @brief Implementation of Raspberry Pi button driver.
 * 
 *        This class is non-copyable and non-movable.
 ********************************************************************************/
class Button
{
public:

    /********************************************************************************
     * @brief Enumeration class representing edges for event detection.
     ********************************************************************************/
    enum class Edge 
    { 
        Rising,  // Rising edge (0 -> 1).
        Falling, // Falling edge (1 -> 0).
        Both,    // Both edges (0 -> 1 or 1 -> 0).
    };

    /********************************************************************************
     * @brief Creates new button connected to specified GPIO pin.
     * 
     * @param pin        Raspberry Pi GPIO pin the button is connected to.
     * @param activeHigh Indicates the active high value (default = high). 
     ********************************************************************************/
    Button(const std::uint8_t pin, const bool activeHigh = true) noexcept;

    /********************************************************************************
     * @brief Deletes button and releases allocated hardware.
     ********************************************************************************/
    ~Button() noexcept;

    /********************************************************************************
     * @brief Provides the GPIO pin the button is connected to.
     * 
     * @return The Raspberry Pi GPIO pin the button is connected to.
     ********************************************************************************/
    std::uint8_t pin() const noexcept;

    /********************************************************************************
     * @brief Indicates if the button is pressed.
     * 
     * @return True if the button is pressed, else false.
     ********************************************************************************/
    bool isPressed() noexcept;

    /********************************************************************************
     * @brief Indicates detected button event on specified edge.
     * 
     * @param edge The edge to be detected (default = rising edge).
     * 
     * @return True if an event on specified edge has been detected, else false.
     ********************************************************************************/
    bool isEventDetected(const Edge edge = Edge::Rising) noexcept;

    Button()                         = delete; // No default constructor.
    Button(const Button&)            = delete; // No copy constructor.
    Button(Button&&)                 = delete; // No move constructor.
    Button& operator=(const Button&) = delete; // No copy assignment.
    Button& operator=(Button&&)      = delete; // No move assignment.

private:
    struct gpiod_line* myLine; // Pointer to GPIO line.
    const bool myActiveHigh;   // Active high value.
    bool myLastInput;          // Previous input value.
};

} // namespace rpi