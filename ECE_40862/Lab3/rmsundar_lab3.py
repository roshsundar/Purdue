#NOTE: Program has to be run as main.py, otherwise it will not work

import network
import ntptime
import utime
from machine import RTC,Timer,TouchPad,Pin
import machine
from neopixel import NeoPixel
import esp32

ssid = 'alpha3'
password = 'Vin0dham'

def connect_to_wifi():
    wifi = network.WLAN(network.STA_IF)
    if not wifi.isconnected():
        print("Connecting to WiFi...")
        wifi.active(True)
        wifi.connect(ssid, password)
        while not wifi.isconnected():
            pass
    print(f"Connected to {ssid}")
    print(f"IP Address: {wifi.ifconfig()[0]}")

connect_to_wifi()

tm = ntptime.time()
tim = utime.localtime(tm-4*3600)
rtc = RTC()
rtc.datetime(tim[0:3]+ tim[6:7] + tim[3:6] + (0,))

def pDate(datetime):
    print('Date: '+ "{:02d}".format(datetime[1]) + '/' + "{:02d}".format(datetime[2]) + '/' + "{:02d}".format(datetime[0]))
    print('Time: ' + "{:02d}".format(datetime[4]) + ':' + "{:02d}".format(datetime[5]) + ':' + "{:02d}".format(datetime[6]))

timer = Timer(0)
timer.init(period=15000,mode=Timer.PERIODIC,callback=lambda t:pDate(rtc.datetime()))

touch = TouchPad(Pin(15))

power_pin = Pin(2,Pin.OUT)
power_pin.value(0)

np_pin = Pin(0, Pin.OUT)   # set GPIO0 to output to drive NeoPixels
np = NeoPixel(np_pin, 1)   # create NeoPixel driver on GPIO0 for 8 pixels
np[0] = (0, 255, 0)

def turn_on_neopixel():
    #print('touch1:',touch.read())
    if touch.read() < 100:
        power_pin.value(1)
        np.write()
    else:
        power_pin.value(0)

timer2 = Timer(1)
timer2.init(period=50,mode=Timer.PERIODIC,callback=lambda t:turn_on_neopixel())

red_led = Pin(13, Pin.OUT)
red_led.on()

esp32.wake_on_ext0(pin = Pin(12,Pin.IN,Pin.PULL_DOWN), level = esp32.WAKEUP_ANY_HIGH)
wake_reason = machine.wake_reason()
if wake_reason == machine.DEEPSLEEP_RESET:
    print('Woke up from deep sleep')
elif wake_reason == machine.PIN_WAKE:
    print('Woke up due to EXT0 Button')
    
def esp32_sleep():
    print('I am going to sleep for 1 minute.')
    red_led.off()
    machine.deepsleep(60000)
timer3 = Timer(2)
timer3.init(period=30000,mode=Timer.PERIODIC,callback=lambda t:esp32_sleep())

