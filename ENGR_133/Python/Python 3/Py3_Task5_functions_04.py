
'''
===============================================================================
ENGR 133 Fa 2020

Assignment Information
	Assignment:     Py3 Task5
	Author:         Roshan Sundar, rmsundar@purdue.edu
	Team ID:        LC1-04

===============================================================================
'''

# Calculate Taylor/McClaurin sum
def Taylor(n,x):
    taylor  = ((-1)**n) * (x**(4*n+3)) / ((4*n+3) * MyFactorial(2*n+1))
    return taylor

# Calculate Factorial
def MyFactorial(n): 
    x = n 
    fact = 1 

    if(x < 0): 
        return -1 
    elif(x==0): 
        return 1 
    else: 
        while x > 0: 
            fact *= x 
            x-=1
        return fact 

'''
===============================================================================
ACADEMIC INTEGRITY STATEMENT
    I have not used source code obtained from any other unauthorized
    source, either modified or unmodified. Neither have I provided
    access to my code to another. The project I am submitting
    is my own original work.
===============================================================================
'''



