import network
import socket
import machine
from machine import RTC, Timer
import esp32

# Vars for the network connection
ssid = 'alpha3'
password = 'Vin0dham'

# Track # of times data has been sent to Thingspeak
counter = 0

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


def SendData():
    global counter
    
    # Read sensor data
    temperature = str(esp32.raw_temperature())
    hall_sensor = str(esp32.hall_sensor())
    print("Temperature is " + temperature)
    print("Hall is " + hall_sensor)
    
    # Send sensor data to ThingSpeak
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    address = socket.getaddrinfo('api.thingspeak.com', 80)[0][-1]
    s.connect(address)
    s.send(bytes("GET http://api.thingspeak.com/update?api_key=85WF7ITSFK8FEMC5&field1="+temperature+"&field2="+hall_sensor+"HTTP/1.0\r\n\r\n", 'utf-8'))
    print(s.recv(1024))
    s.close()
    
    # Check if 5 mins of data has been sent
    counter += 1
    if counter >= 10:
        Tim.deinit()
        print("Done!")
        return
    
    
connect_to_wifi()
Tim = Timer(1)
Tim.init(mode=Timer.PERIODIC, period=30000, callback=lambda t:SendData())
