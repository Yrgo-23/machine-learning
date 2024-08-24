#pragma once

#include <cstdint>

struct gpiod_line;

namespace yrgo 
{
namespace rpi
{

class Button
{
public:

    enum class Edge { Rising, Falling, Both };

    Button() = delete;
    Button(const std::uint8_t pin, const bool activeHigh = true);
    ~Button();

    std::uint8_t pin() const;
    bool isPressed();
    bool isEventDetected(const Edge edge = Edge::Rising);

private:
    struct gpiod_line* myLine;
    const bool myActiveHigh;
    bool myLastInput;
};

} // namespace rpi
} // namespace yrgo