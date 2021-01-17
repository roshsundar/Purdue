# -*- coding: utf-8 -*-
"""
Created on Thu Sep 10 08:38:25 2020

ENGR 133 Fa 2020

Assignment Information
	Assignment:     Py1 Task 5
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
"""
import math as m
rad = int(input('What is radius: '))
h = int(input('What is height: '))
area = m.pi * rad * (rad + m.sqrt((rad**2) + (h**2)))
print('The area of the cone is ' + str(area))
