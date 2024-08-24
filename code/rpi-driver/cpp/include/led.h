#pragma once

#include <cstdint>

struct gpiod_line;

namespace yrgo 
{
namespace rpi 
{

class Led 
{
public:
    Led() = default;
    Led(const std::uint8_t pin, const bool enabled = false);
    ~Led();

    std::uint8_t pin() const;
    bool isEnabled() const;

    void on();
    void off();
    void toggle();

    void blink(const std::uint16_t blinkSpeedMs);

private:
    struct gpiod_line* myLine;
};

} // namespace rpi
} // namespace yrgo