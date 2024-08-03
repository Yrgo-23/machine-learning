/********************************************************************************
 * @brief Driver for serial transmission via USART.
 ********************************************************************************/
#pragma once

#include "utils.h"

namespace driver 
{
namespace serial 
{
namespace
{

/********************************************************************************
 * @brief Initializes serial transmission with specified baud rate.
 *
 * @param baudRateKbps The baud rate (transmission speed) in kilobits per second
 *                     default = 9600 kbps).
 ********************************************************************************/
void init(const uint32_t baudRateKbps = 9600);

/********************************************************************************
 * @brief Prints formatted string in serial terminal. If the formatted string
 *        contains format specifiers, the additional arguments are formatted
 *        as inserted into the format string.
 *
 * @tparam Args  Parameter pack containing an arbitrary number of arguments.
 *
 * @param format Reference to string containing the text to print.
 * @param args   Parameter pack containing potential additional arguments.
 *
 * @return True if the string was printed, else false.
 ********************************************************************************/
template <typename... Args>
bool printf(const char* format, const Args&... args);

} // namespace
} // namespace serial
} // namespace driver

#include "serial_impl.h"
