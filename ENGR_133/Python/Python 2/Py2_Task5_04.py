# -*- coding: utf-8 -*-
'''
===============================================================================
ENGR 133 Fa 2020

Assignment Information
	Assignment:     Py2 Task5
	Author:         Roshan Sundar, rmsundar@purdue.edu
	Team ID:        LC1-04
	
Contributors:   Jackson Bitterolf  
                Ayush Viswanathan 
                Nolan Hays
	My contributor(s) helped me:	
	[ ] understand the assignment expectations without
		telling me how they will approach it.
	[ ] understand different ways to think about a solution
		without helping me plan my solution.
	[ ] think through the meaning of a specific error or
		bug present in my code without looking at my code.
	Note that if you helped somebody else with their code, you
	have to list that person as a contributor here as well.
===============================================================================
'''

import Py2_Task5_discriminant_04

a = int(input("Input a: "))
b = int(input("Input b: "))
c = int(input("Input c: "))
d = int(input("Input d: "))

print('The Inputs are: ')
print(f"a={a}, b={b}, c={c}, d={d}")

disc = Py2_Task5_discriminant_04.discriminant(a,b,c,d)

case1, case2, case3 = False, False, False

if(disc > 0):
    case1 = True
elif (disc == 0):
    case2 = True
else:
    case3 = True
    
print(f"Real and distinct three roots: {case1}")
print(f"Real with at least two equal roots: {case2}")
print(f"Conjugate pair of complex roots:: {case3}")

'''
===============================================================================
ACADEMIC INTEGRITY STATEMENT
    I have not used source code obtained from any other unauthorized
    source, either modified or unmodified. Neither have I provided
    access to my code to another. The project I am submitting
    is my own original work.
===============================================================================
'''