from machine import Pin
from neopixel import NeoPixel
from time import sleep

power_pin = Pin(2,Pin.OUT).value(1)

np_pin = Pin(0, Pin.OUT)   # set GPIO0 to output to drive NeoPixels
np = NeoPixel(np_pin, 1)   # create NeoPixel driver on GPIO0 for 8 pixels
np[0] = (255, 0, 0)
np.write()

btn = Pin(38, Pin.IN)

presses = 0

while presses < 5:
    if btn.value() == 0:
        presses += 1
        print(presses)
        np[0] = (0, 255, 0)
        np.write()
        while btn.value() == 0:
            sleep(0.01)
        np[0] = (255, 0, 0)
        np.write()

power_pin = Pin(2,Pin.OUT).value(0)
print('You have successfully implemented LAB1!')