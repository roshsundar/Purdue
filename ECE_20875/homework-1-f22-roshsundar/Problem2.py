#!/usr/bin/python3
from datetime import datetime

n = 21
# Your code should be below this 
if (n < 1 or n > 31):
    print('Not valid')
    quit()

d = datetime(2022, 1, n)
if d.weekday() > 4:
    print('Weekend')
else:
    print('Weekday')