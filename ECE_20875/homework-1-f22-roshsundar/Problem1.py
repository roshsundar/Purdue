#!/usr/bin/python3
number = 100
# Your code should be below this line
if (number % 2 == 0) and (number > 0) and (((5 * (number ** 2) + 4) ** 0.5).is_integer() or ((5 * (number ** 2) - 4) ** 0.5).is_integer()):
    print("Yes")
else:
    print("No")