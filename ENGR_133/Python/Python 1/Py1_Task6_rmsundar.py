# -*- coding: utf-8 -*-
'''
===============================================================================
ENGR 133 Fa 2020

Assignment Information
	Assignment:     Py1 Task6
	Author:         Roshan Sundar, rmsundar@purdue.edu
	Team ID:        LC1-04
===============================================================================
'''
import random
from fractions import Fraction

random.seed(int(input("Enter  the  seed:  ")))
rand1 = random.uniform(1.00, 100.00)
rand2 = random.uniform(1.00, 100.00)
rand3 = random.uniform(1.00, 100.00)

round_rand1 = round(rand1, 2)
round_rand2 = round(rand2, 2)
round_rand3 = round(rand3, 2)
round_decSum = round_rand1 + round_rand2 + round_rand3
round_Sum = round(round_decSum, 2)

frac_rand1 = Fraction(round_rand1).limit_denominator()
frac_rand2 = Fraction(round_rand2).limit_denominator()
frac_rand3 = Fraction(round_rand3).limit_denominator()
frac_Sum = Fraction(round_Sum).limit_denominator()

print(f'First Random Number : {round_rand1}')
print(f'Second Random Number : {round_rand2}')
print(f'Third Random Number : {round_rand3}')

print(f"Sum from decimals : {round_rand1} + {round_rand2} + {round_rand3} = {round_Sum}")
print(f"Sum from fractions : {frac_rand1} + {frac_rand2} + {frac_rand3} = {frac_Sum}")