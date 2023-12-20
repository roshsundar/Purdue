from machine import RTC
from machine import Timer
from time import sleep
from machine import ADC
from machine import Pin
import machine
from machine import PWM

switch_state = 0
last_switch_state = 0
switch_pressed = 0
led_state = 1

rtc = RTC()
adc = ADC(Pin(33))
switch = Pin(38,Pin.IN,Pin.PULL_UP)

year = int(input('Year? '))
month = int(input('Month? '))
day = int(input('Day? '))
weekday = int(input('Weekday? '))
hour = int(input('Hour? '))
minute = int(input('Minute? '))
second = int(input('Second? '))
microsecond = int(input('Microsecond? '))

rtc.datetime((year,month,day,weekday,hour,minute,second,microsecond))

def printDate(datetime):
    print('Date: '+ "{:02d}".format(datetime[0]) + '/' + "{:02d}".format(datetime[1]) + '/' + "{:02d}".format(datetime[2]))
    print('Time:' + "{:02d}".format(datetime[4]) + ':' + "{:02d}".format(datetime[5]) + ':' + "{:02d}".format(datetime[6]))

def switch_pressed(pin):
    global switch_state
    global switch_pressed
    global led_state

    if switch_state == 1:
        led_state = int(not led_state)
        switch_pressed = 1

def debounce(timer):
    global switch_state, last_switch_state

    current_state = switch.value()

    if current_state != last_switch_state:
        switch_state = current_state

timer = Timer(0)
timer.init(period=30000,mode=Timer.PERIODIC,callback=lambda t:printDate(rtc.datetime()))

adc_timer = Timer(1)
adc_timer.init(period=100,mode=Timer.PERIODIC,callback= lambda t:adc.read())

debounce_timer = Timer(2)
debounce_timer.init(period=10, mode=machine.Timer.PERIODIC, callback=debounce)
switch.irq(trigger=Pin.IRQ_FALLING,handler = switch_pressed)

frequency = 10
duty_cycle = 512
PWM(Pin(14),freq=frequency,duty=duty_cycle)

while True:
    if switch_pressed == 1:
        adc_value = adc.read()
        if led_state == 0:
            frequency = int(1 + (adc_value / 4095) * 10)
            pwm = PWM(Pin(14), freq=frequency, duty=duty_cycle)
        else:
            duty_cycle = int((adc_value / 4095) * 512)
            pwm = PWM(Pin(14), freq=frequency, duty=duty_cycle)
    sleep(0.1)