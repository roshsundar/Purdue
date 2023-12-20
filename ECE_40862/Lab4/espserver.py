import network
import socket
import machine
from machine import RTC, Pin, Timer
import esp32

# Global variables
temp = 0  # measure temperature sensor data
hall = 0  # measure hall sensor data
red_led_state = "" # string, check state of red led, ON or OFF

# Vars for the network connection
ssid = 'alpha3'
password = 'Vin0dham'


def web_page():
    """Function to build the HTML webpage which should be displayed
    in client (web browser on PC or phone) when the client sends a request
    the ESP32 server.
    
    The server should send necessary header information to the client
    (YOU HAVE TO FIND OUT WHAT HEADER YOUR SERVER NEEDS TO SEND)
    and then only send the HTML webpage to the client.
    
    Global variables:
    temp, hall, red_led_state
    """
    
    html_webpage = """<!DOCTYPE HTML><html>
    <head>
    <title>ESP32 Web Server</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.7.2/css/all.css" integrity="sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr" crossorigin="anonymous">
    <style>
    html {
     font-family: Arial;
     display: inline-block;
     margin: 0px auto;
     text-align: center;
    }
    h1 { font-size: 3.0rem; }
    p { font-size: 3.0rem; }
    .units { font-size: 1.5rem; }
    .sensor-labels{
      font-size: 1.5rem;
      vertical-align:middle;
      padding-bottom: 15px;
    }
    .button {
        display: inline-block; background-color: #e7bd3b; border: none; 
        border-radius: 4px; color: white; padding: 16px 40px; text-decoration: none;
        font-size: 30px; margin: 2px; cursor: pointer;
    }
    .button2 {
        background-color: #4286f4;
    }
    </style>
    </head>
    <body>
    <h1>ESP32 WEB Server</h1>
    <p>
    <i class="fas fa-thermometer-half" style="color:#059e8a;"></i> 
    <span class="sensor-labels">Temperature</span> 
    <span>"""+str(temp)+"""</span>
    <sup class="units">&deg;F</sup>
    </p>
    <p>
    <i class="fas fa-bolt" style="color:#00add6;"></i>
    <span class="sensor-labels">Hall</span>
    <span>"""+str(hall)+"""</span>
    <sup class="units">V</sup>
    </p>
    <p>
    RED LED Current State: <strong>""" + red_led_state + """</strong>
    </p>
    <p>
    <a href="/?red_led=on"><button class="button">RED ON</button></a>
    </p>
    <p>
    <a href="/?red_led=off"><button class="button button2">RED OFF</button></a>
    </p>
    </body>
    </html>"""
    return html_webpage

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
    
connect_to_wifi()
    
# Initialize the webpage
red_led = Pin(13, Pin.OUT)
red_led.value(0)
red_led_state = "OFF"
temp = str(esp32.raw_temperature())
hall = str(esp32.hall_sensor())
htmlwebpage = web_page()

# Start listening for connections
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind(('', 80))
s.listen(5)

while(True):
    # Connection recieved, fetch data
    conn, addr = s.accept()
    request = conn.recv(1024)
    request = str(request)
    
    # Turn the LED on/off as needed
    redled_on = request.find('/?red_led=on')
    redled_off = request.find('/?red_led=off')
    if redled_on == 6:
        red_led.value(1)
        red_led_state = "ON"
    if redled_off == 6:
        red_led.value(0)
        red_led_state = "OFF"
    
    # Update the Webpage again
    temp = str(esp32.raw_temperature())
    hall = str(esp32.hall_sensor())
    response = web_page()
    
    # Send response back to client
    conn.send('HTTP/1.1 200 OK\n')
    conn.send('Content-Type: text/html\n')
    conn.send('Connection: close\n\n')
    conn.sendall(response)
    conn.close()
