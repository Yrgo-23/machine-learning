/********************************************************************************
 * @brief Implementation details of serial driver.
 *
 * @note Don't include this file directly.
 ********************************************************************************/
#pragma once

#include <stdio.h>

#include "serial.h"

namespace driver 
{
namespace serial 
{
namespace 
{
namespace detail
{

static constexpr char CarriageReturn{'\r'};
static constexpr char NewLine{'\n'};

// -----------------------------------------------------------------------------
constexpr uint16_t getBaudRateValue(const uint32_t baudRateKbps)
{
    return baudRateKbps == 9600 ? 103 :
        utils::round<uint16_t>(F_CPU / 16.0 * baudRateKbps);
}

// -----------------------------------------------------------------------------
void printChar(const char c)
{
    while (utils::read(UCSR0A, UDRE0) == 0);
    UDR0 = c;
}

// -----------------------------------------------------------------------------
void print(const char* s)
{
    for (const char* i{s}; *i; ++i)
    {
        printChar(*i);

        if (*i == detail::CarriageReturn)
        {
            printChar(detail::NewLine);
        }
    }
}
} // namespace detail

// -----------------------------------------------------------------------------
void init(const uint32_t baudRateKbps)
{
    static bool serialInitialized{false};

    if (!serialInitialized)
    {
        utils::set(UCSR0B, TXEN0);
        utils::set(UCSR0C, UCSZ00, UCSZ01);
        UBRR0 = detail::getBaudRateValue(baudRateKbps);
        UDR0 = detail::CarriageReturn;
        serialInitialized = true;
    }
}

// -----------------------------------------------------------------------------
template <typename... Args>
bool printf(const char* format, const Args&... args)
{
    if (format == nullptr) { return false; }
    if (sizeof...(args) > 0)
    {
        const int length{snprintf(nullptr, 0, format, nullptr)};
        char* buffer{(char*)malloc(sizeof(char) * length)};
        if (!buffer) { return false; }
        buffer[0] = '\0';
        sprintf(buffer, format, args...);
        detail::print(buffer);
        free(buffer);
    }
    else
    {
        detail::print(format);
    }
    return true;
}

} // namespace
} // namespace serial
} // namespace driver
