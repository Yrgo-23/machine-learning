from gpio import Led, Button, Event
from numbers import Number

ledsEnabled = False

# ------------------------------------------------------------------------------
def buttonPressedCallback(buttonPin: int) -> None:
    global ledsEnabled
    ledsEnabled = not ledsEnabled

# ------------------------------------------------------------------------------
def blinkLeds(leds: tuple[Led], blinkSpeedMs: Number) -> None:
    disableLeds(leds)
    for led in leds:
        led.on()
        led.delayMs(blinkSpeedMs)
        led.off()

# ------------------------------------------------------------------------------
def disableLeds(leds: tuple[Led]) -> None:
    for led in leds:
        led.off()

# ------------------------------------------------------------------------------
def main() -> None:
    leds = (Led(17), Led(22), Led(23))
    button = Button(27)
    button.addCallback(buttonPressedCallback, Event.RisingEdge, bounceTime=500)
    while True:
        if ledsEnabled:
            blinkLeds(leds, 100)
        else:
            disableLeds(leds)

# ------------------------------------------------------------------------------
if __name__ == "__main__":
   main()