
'''
===============================================================================
ENGR 133 Fa 2020

Assignment Information
	Assignment:     Py3 Task5
	Author:         Roshan Sundar, rmsundar@purdue.edu
	Team ID:        LC1-04

===============================================================================
'''
import Py3_Task5_functions_04
import sys

# Get input and check if datatype correct
try:
    a = float(input("Enter the lower limit of integration: "))
    b = float(input("Enter the upper limit of integration: "))
except:
    print("Error1")
    sys.exit()
try:
    r = int(input("Enter the number of decimal places for convergence: "))
    n_max = int(input("Enter the maximum number of terms: "))
except:
    print("Error2")
    sys.exit()

print("Approximations: ")

tsum = 0
tsum_last = 0
count = 0
# Approximate Integral
for n in range(0, n_max):
    if (count == 2):
        print(f"The integral from {a} to {b} is estimated to be {tsum}")
        print(f"Total number of terms: {n}")
        sys.exit()
    tsum_last = tsum
    tchange = Py3_Task5_functions_04.Taylor(n,b) - Py3_Task5_functions_04.Taylor(n,a)
    tsum += tchange
    tsum = round(tsum, r)
    print(f"n = {n}: sum = {tsum}")
    
    if (tsum_last == tsum):
        count += 1

print(f"Error: The approximation did not converge to {r} decimal places with only {n+1} terms.")


'''
===============================================================================
ACADEMIC INTEGRITY STATEMENT
    I have not used source code obtained from any other unauthorized
    source, either modified or unmodified. Neither have I provided
    access to my code to another. The project I am submitting
    is my own original work.
===============================================================================
'''



