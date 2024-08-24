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
 ********************************************************************************/
class Button
{
public:

    /********************************************************************************
     * @brief Edges for event detection.
     * 
     * @param Rising  Rising edge (0 -> 1).
     * @param Falling Falling edge (1 -> 0).
     * @param Both    Both edges (0 -> 1 or 1 -> 0).
     ********************************************************************************/
    enum class Edge { Rising, Falling, Both };

    /********************************************************************************
     * @brief Default destructor deleted.
     ********************************************************************************/
    Button() = delete;

    /********************************************************************************
     * @brief Creates new button connected to specified GPIO pin.
     * 
     * @param pin        Raspberry Pi GPIO pin the button is connected to.
     * @param activeHigh Indicates the active high value (default = high). 
     ********************************************************************************/
    Button(const std::uint8_t pin, const bool activeHigh = true);

    /********************************************************************************
     * @brief Deletes button and releases allocated hardware resources.
     ********************************************************************************/
    ~Button();

    /********************************************************************************
     * @brief Provides the GPIO pin the button is connected to.
     * 
     * @return The Raspberry Pi GPIO pin the button is connected to.
     ********************************************************************************/
    std::uint8_t pin() const;

    /********************************************************************************
     * @brief Indicates if the button is pressed.
     * 
     * @return True if the button is pressed, else false.
     ********************************************************************************/
    bool isPressed();

    /********************************************************************************
     * @brief Indicates detected button event on specified edge.
     * 
     * @param edge The edge to be detected (default = rising edge).
     * 
     * @return True if an event on specified edge has been detected, else false.
     ********************************************************************************/
    bool isEventDetected(const Edge edge = Edge::Rising);

private:
    struct gpiod_line* myLine;
    const bool myActiveHigh;
    bool myLastInput;
};

} // namespace rpi