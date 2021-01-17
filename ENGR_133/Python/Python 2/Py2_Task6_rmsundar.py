# -*- coding: utf-8 -*-
'''
===============================================================================
ENGR 133 Fa 2020

Assignment Information
	Assignment:     Py2 Task6
	Author:         Roshan Sundar, rmsundar@purdue.edu
	Team ID:        LC1-04
===============================================================================
'''


import math as m

n1 = float(input("Input refractive index medium 1 [unitless]: ")) 
n2 = 1.3
d1 = 3.8
d2 = 9.1
d3 = 'N/A' # Find
theta1 = float(input("Input incoming angle [degrees]: "))
theta2 = 'N/A' # Find
thetaC = 'N/A' # Find
ray = 'N/A' # Find

def theta2_Calc(_n1, _n2, _theta1):
    x = m.sin(m.radians(_theta1))
    y = (_n1/_n2) * x
    _theta2 = m.degrees(m.asin(y))
    return _theta2

def d3_Calc(_d1, _d2, _theta1, _theta2):
    _d3 = (_d1 * m.tan(m.radians(_theta1))) + (_d2 * m.tan(m.radians(_theta2)))
    return _d3

if(n1 > n2):
    thetaC = m.degrees(m.asin(n2/n1))
    
    if (theta1 < thetaC):
        ray = 'Refraction'
        theta2 = theta2_Calc(n1,n2,theta1)
        d3 = d3_Calc(d1, d2, theta1, theta2)
        
        theta2 = round(theta2,1)
        thetaC = round(thetaC,1)
        d3 = round(d3,1)
    else:
        ray = 'total internal reflection'
        thetaC = round(thetaC,1)
elif(n1 == n2):
    ray = 'Straight Line Refraction'
    theta2 = theta1
    d3 = d3_Calc(d1, d2, theta1, theta2)
    
    theta2 = round(theta2,1)
    d3 = round(d3,1)
else:
    ray = 'Refraction'
    theta2 = theta2_Calc(n1,n2,theta1)
    d3 = d3_Calc(d1, d2, theta1, theta2)
    
    theta2 = round(theta2,1)
    d3 = round(d3,1)

print('')
print(f"There is {ray} with a leaving angle of {theta2} degrees.")
print(f"The ending distance for the light ray is {d3} cm.")
print(f"For these two media, the critical angle is {thetaC} degrees.")

'''
===============================================================================
ACADEMIC INTEGRITY STATEMENT
    I have not used source code obtained from any other unauthorized
    source, either modified or unmodified. Neither have I provided
    access to my code to another. The project I am submitting
    is my own original work.
===============================================================================
'''