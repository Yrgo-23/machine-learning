from enum import Enum
from numbers import Number
from typing import Callable

import RPi.GPIO as GPIO
GPIO.setwarnings(False) 
GPIO.setmode(GPIO.BCM) 

class Event(Enum):
    RisingEdge = 0
    FallingEdge = 1
    BothEdges = 2

class Led:
   
    # ------------------------------------------------------------------------------
    def __init__(self, pin: int, startVal: int = 0) -> None:
        self._pin = pin
        self._enabled = False
        GPIO.setup(self._pin, GPIO.OUT)
        GPIO.output(self._pin, startVal)

    # ------------------------------------------------------------------------------
    def __del__(self) -> None:
        GPIO.output(self._pin, 0)
        GPIO.setup(self._pin, GPIO.IN)

    # ------------------------------------------------------------------------------
    def pin(self) -> int:
        return self._pin

    # ------------------------------------------------------------------------------
    def isEnabled(self) -> bool:
        return self._enabled
    
    # ------------------------------------------------------------------------------
    def on(self) -> None:
        GPIO.output(self._pin, 1)
        self._enabled = True

    # ------------------------------------------------------------------------------
    def off(self) -> None:
        GPIO.output(self._pin, 0)
        self._enabled = False
    
    # ------------------------------------------------------------------------------
    def toggle(self) -> None:
        if self.isEnabled():
            self.off()
        else:
            self.on()

    # ------------------------------------------------------------------------------
    def blink(self, blinkSpeedMs: Number) -> None:
        for i in range(2):
            self.toggle()
            self.delayMs(blinkSpeedMs)

    # ------------------------------------------------------------------------------
    @staticmethod
    def delayMs(delayTimeMs: Number) -> None:
        import time
        time.sleep(delayTimeMs / 1000.0)

class Button:

    # ------------------------------------------------------------------------------
    def __init__(self, pin: int) -> None:
        self._pin = pin
        GPIO.setup(self._pin, GPIO.IN)

    # ------------------------------------------------------------------------------
    def __del__(self) -> None:
        self.removeCallback()

    # ------------------------------------------------------------------------------
    def pin(self) -> int:
        return self._pin
    
    # ------------------------------------------------------------------------------
    def isPressed(self) -> bool:
        return GPIO.input(self._pin)
    
    # ------------------------------------------------------------------------------
    def addCallback(self, callback: Callable, eventType: Event, bounceTime: int = None) -> bool:
        if eventType == Event.RisingEdge:
            GPIO.add_event_detect(self._pin, GPIO.RISING, callback=callback, bouncetime=bounceTime)
        elif eventType == Event.FallingEdge:
            GPIO.add_event_detect(self._pin, GPIO.FALLING, callback=callback, bouncetime=bounceTime)
        elif (eventType == Event.BothEdges):
            GPIO.add_event_detect(self._pin, GPIO.BOTH, callback=callback, bouncetime=bounceTime)
        else:
            print("Failed to enable event for type " + str(eventType) + "!\n")
            return False 
        return True
    
    # ------------------------------------------------------------------------------
    def removeCallback(self) -> None:
        GPIO.remove_event_detect(self._pin)
