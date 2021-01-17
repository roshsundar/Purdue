# -*- coding: utf-8 -*-
'''
===============================================================================
ENGR 133 Fa 2020

Assignment Information
	Assignment:     Py2 Task7
	Author:         Roshan Sundar, rmsundar@purdue.edu
	Team ID:        LC1-04
===============================================================================
'''

def pressure(R,T,Vm,a,b):
    P = ((R*T)/(Vm-b)) - (a/(Vm**2))
    return P

def temperature(R,P,Vm,a,b):
    T = (P+(a/(Vm**2))) * (Vm-b) * (1/R)
    return T

'''
===============================================================================
ACADEMIC INTEGRITY STATEMENT
    I have not used source code obtained from any other unauthorized
    source, either modified or unmodified. Neither have I provided
    access to my code to another. The project I am submitting
    is my own original work.
===============================================================================
'''