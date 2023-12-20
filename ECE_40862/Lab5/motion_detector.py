import network
import urequests
import machine
from machine import RTC, Timer, Pin, SoftI2C
from neopixel import NeoPixel
import mpu6050
from utime import sleep
import ujson

# Global Vars
status = 0

# Acceleration Vars
accelX_thresh = 0.05
accelY_thresh = 0.05
accelZ_thresh = 0.05


# Vars for the network connection
ssid = 'alpha3'
password = 'Vin0dham'
thingspeak_url = "https://api.thingspeak.com/channels/2375285/fields/1.json?api_key=X7KWPG9N9F97SOCG&results=2"
ifttt_url = "https://maker.ifttt.com/trigger/accel_data/json/with/key/cuEM9arQXfJlSoyHRr_B21"

# Function to connect to network
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
    
# Get the activation status from ThingSpeak
def FetchStatus():
    global status
    request = urequests.get(thingspeak_url)
    status = int(request.json()['feeds'][-1]['field1'])
    print(f"Activation Status: {status}")

# Send data to IFTTT
def SendData(accelX, accelY, accelZ):
    data = {
    'X': accelX,
    'Y': accelY,
    'Z': accelZ
    }
    json_data = ujson.dumps(data)
    response = urequests.post(ifttt_url, data=json_data)
    response.close()

connect_to_wifi()
Tim = Timer(1)
Tim.init(mode=Timer.PERIODIC, period=30000, callback=lambda t:FetchStatus())

# LEDs init
power_pin = Pin(2,Pin.OUT) # power control pin for neopixel
np_pin = Pin(0, Pin.OUT)   # set GPIO0 to output to drive NeoPixels
np = NeoPixel(np_pin, 1)   # create NeoPixel driver on GPIO0 for 8 pixels
np[0] = (0, 255, 0)
red_led = Pin(13, Pin.OUT)

# mpu6050 init
power_pin.value(1)
i2c = SoftI2C(scl=Pin(14), sda=Pin(22))
mpu= mpu6050.accel(i2c)

FetchStatus()
while (1):
    if (status):
        # Turn on NeoPixel
        power_pin.value(1)
        np.write()
        
        # check accelerometer
        vals = mpu.get_values()
        if (abs(vals['AcX']) >= 0.07 or abs(vals['AcY']) >= 0.07 or abs(vals['AcY']) >= 1.0):
            red_led.on()
            SendData(vals['AcX'], vals['AcY'], vals['AcZ'])
        else:
            red_led.off()
        sleep(0.5)
    else:
        power_pin.value(0)
        red_led.off()