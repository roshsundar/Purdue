# -*- coding: utf-8 -*-
'''
===============================================================================
ENGR 133 Fa 2020

Assignment Information
	Assignment:     Py2 Task3
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

speed = 700 
time = 2 
power = 500 
air_density = 1.23 
wind_velocity = 6 
power_coefficient = .4   

def windTurbineArea (p,ad,wv,pc): 
    area = round((2*p)/(ad * (wv**3) * pc),2) 
    return area 

def distanceBike (s,t): 
    d = round(s * t,2) 
    return d 

def main(): 
    area = windTurbineArea( power, air_density, wind_velocity, power_coefficient) 
    print(f'The area of the blade sweep is {area} [m^2]') 

    distance = distanceBike(speed,time) 
    print(f'The distance traveled by the bike is {distance} [m]') 

main() 

'''
===============================================================================
ACADEMIC INTEGRITY STATEMENT
    I have not used source code obtained from any other unauthorized
    source, either modified or unmodified. Neither have I provided
    access to my code to another. The project I am submitting
    is my own original work.
===============================================================================
'''