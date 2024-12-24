/********************************************************************************
 * @brief Utility functions for the Linux GPIO driver.
 ********************************************************************************/
#pragma once

#include <stdint.h>
#include <stdbool.h>

struct gpiod_line; /* GPIO line structure. */

#ifdef __cplusplus
namespace rpi 
{
extern "C" 
{
#endif 

/********************************************************************************
 * @brief Enumeration representing data direction of GPIO lines.
 ********************************************************************************/
enum gpiod_line_direction 
{ 
    GPIOD_LINE_DIRECTION_IN,  /* Input line. */
    GPIOD_LINE_DIRECTION_OUT, /* Output line. */
}; 

/********************************************************************************
 * @brief Enumeration representing edges for event detection.
 ********************************************************************************/
enum gpiod_line_edge 
{ 
    GPIOD_LINE_EDGE_RISING,  /* Rising edge (0 -> 1). */
    GPIOD_LINE_EDGE_FALLING, /* Falling edge (1 -> 0). */
    GPIOD_LINE_EDGE_BOTH,    /* Both edges (0 -> 1 or 1 -> 0). */
};  

/********************************************************************************
 * @brief Creates new GPIO line for a device.
 * 
 * @param pin       Raspberry Pi GPIO pin the device is connected to.
 * @param direction Data direction of the device.
 * 
 * @return Pointer to the new GPIO line.
 ********************************************************************************/
struct gpiod_line* gpiod_line_new(const uint8_t pin, const enum gpiod_line_direction direction);


/********************************************************************************
 * @brief Toggles the output of specified GPIO line.
 * 
 * @param self Pointer to the GPIO line to toggle.
 ********************************************************************************/
void gpiod_line_toggle(struct gpiod_line* self);

/********************************************************************************
 * @brief Blinks the output value of specified GPIO line.
 * 
 * @param self           Pointer to the GPIO line to blink.
 * @param blink_speed_ms The blink speed measured in milliseconds.
 ********************************************************************************/
void gpiod_line_blink(struct gpiod_line* self, const uint16_t blink_speed_ms);

/********************************************************************************
 * @brief Indicates detected event on specified GPIO line.
 * 
 * @param self           Pointer to the GPIO line to detect.
 * @param edge           The edge to be detected.
 * @param previous_input Pointer to variable holding the previous input value
 *                       of the GPIO line.
 * 
 * @return True if an event on specified edge has been detected, else false.
 ********************************************************************************/
bool gpiod_line_event_detected(struct gpiod_line* self, const enum gpiod_line_edge edge, 
                               bool* previous_input);

#ifdef __cplusplus
} // extern "C"

} // namespace rpi
#endif