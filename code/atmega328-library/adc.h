/********************************************************************************
 * @brief Driver for the ATmega328P ADC.
 ********************************************************************************/
#pragma once

#include "utils.h"

namespace driver 
{
namespace adc 
{

/********************************************************************************
 * @brief Struct containing pin names for each analog pin A0 - A5.
 ********************************************************************************/
struct Pin 
{
    static constexpr uint8_t A0{0}; // Pin A0 = 0
    static constexpr uint8_t A1{1}; // Pin A1 = 1
    static constexpr uint8_t A2{2}; // Pin A2 = 2
    static constexpr uint8_t A3{3}; // Pin A3 = 3
    static constexpr uint8_t A4{4}; // Pin A4 = 4
    static constexpr uint8_t A5{5}; // Pin A5 = 5
};

/********************************************************************************
 * @brief Struct containing port names for each analog pin A0 - A5.
 ********************************************************************************/
struct Port
 {
    static constexpr uint8_t C0{14}; // PORTC0 = pin 14
    static constexpr uint8_t C1{15}; // PORTC1 = pin 15
    static constexpr uint8_t C2{16}; // PORTC2 = pin 16
    static constexpr uint8_t C3{17}; // PORTC3 = pin 17
    static constexpr uint8_t C4{18}; // PORTC4 = pin 18
    static constexpr uint8_t C5{19}; // PORTC5 = pin 10
};

/********************************************************************************
 * @brief Initializes AD converter by doing a test conversion.
 ********************************************************************************/
void init(void);

/********************************************************************************
 * @brief Reads the analog input of specified pin and returns the corresponding
 *        duty cycle as a floating-point number in the range 0 - 1.
 *
 * @param pin The analog pin to read (A0 - A5 / PORTC0 - PORTC5).
 *
 * @return The corresponding duty cycle as a floating-pointer number in the
 *         range 0 - 1 or 0 if an invalid pin was selected.
 ********************************************************************************/
double getDutyCycle(const uint8_t pin);

/********************************************************************************
 * @brief Reads analog input from specified pin and returns the corresponding
 *        10-bit digital value 0 - 1023.
 *
 * @param pin The analog pin to read (A0 - A5 / PORTC0 - PORTC5).
 * 
 * @return The corresponding 10-bit digital value 0 - 1023 or 0 if an 
 *         invalid pin was specified.
 ********************************************************************************/
uint16_t read(const uint8_t pin);

/********************************************************************************
 * @brief Reads the analog input of specified pin and calculates the 
 *        corresponding on- and off-time in milliseconds.
 *
 * @param pin          The analog pin to read (A0 - A5 / PORTC0 - PORTC5).
 * @param pwmPeriodMs  The PWM period (on-time + off_time) in milliseconds.
 * @param pwmOnTimeMs  Reference to variable storing the calculated on time 
 *                     measured in milliseconds.
 * @param pwmOffTimeMs Reference to variable storing the calculated off time 
 *                     measured in milliseconds.
 * 
 * @return True upon successful calculation of requested values, else false
 *         if an invalid pin number was specified.
 ********************************************************************************/
bool getDutyCycleParameters_ms(const uint8_t pin, 
                               const uint8_t pwmPeriodMs, 
                               uint8_t& pwmOnTimeMs, 
                               uint8_t& pwmOffTimeMs);

/********************************************************************************
 * @brief Reads the analog input of specified pin and calculates the 
 *        corresponding on- and off-time in microseconds.
 *
 * @param pin          The analog pin to read (A0 - A5 / PORTC0 - PORTC5).
 * @param pwmPeriodUs  The PWM period (on-time + off_time) microseconds.
 * @param pwmOnTimeUs  Reference to variable storing the calculated on time 
 *                     measured in microseconds.
 * @param pwmOffTimeUs Reference to variable storing the calculated off time
 *                     measured in microseconds.
 * 
 * @return True upon successful calculation of requested values, else false
 *         if an invalid pin number was specified.
 ********************************************************************************/
bool getDutyCycleParameters_us(const uint8_t pin,
                               const uint16_t pwmPeriodUs, 
                               uint16_t& pwmOnTimeUs, 
                               uint16_t& pwmOffTimeUs);
} // namespace adc
} // namespace driver