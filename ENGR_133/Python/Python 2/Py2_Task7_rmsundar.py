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
import Py2_Task7_functions_rmsundar

R = 0.0820573661
T = float(input("Input Initial Temperature in Kelvin: "))
Vm = float(input("Input molar volume in L/mol: "))
a = 6.49
b = 0.0562

T_new = 'N/A'
T_change = 'N/A'
P_new = 'N/A'

P = Py2_Task7_functions_rmsundar.pressure(R,T,Vm,a,b)

def output():
    print("")
    print(f"Molar volume = {Vm} [L/mol]")
    print(f"Initial temperature = {T} [K]")
    print(f"Parameter a = {a} [L^2*atm/(mol^2)]")
    print(f"Parameter b = {b} [L/mol]")
    print(f"Resulting pressure = {P} [atm]")
    print(f"Required temperature increment for in-range pressure = {T_change} [K]")
    print(f"New temperature = {T_new} [K]")
    print(f"New pressure = {P_new} [atm]")

if(0<P<100 or Vm < 0):
    print("Error: Pressure or Molar Volume can't be negative")
elif (round(P,3) > 1.2):
    T_new = Py2_Task7_functions_rmsundar.temperature(R,1.2,Vm,a,b)
    T_change = T_new - T
    P_new = Py2_Task7_functions_rmsundar.pressure(R,T_new,Vm,a,b)
    
    T = round(T,2)
    P = round(P,2)
    T_new = round(T_new,2)
    T_change = round(T_change,2)
    P_new = round(P_new,2)
    output()
elif (round(P,3) < 1.1):
    T_new = Py2_Task7_functions_rmsundar.temperature(R,1.1,Vm,a,b)
    T_change = T_new - T
    P_new = Py2_Task7_functions_rmsundar.pressure(R,T_new,Vm,a,b)
    
    output()
else:
    output()
    

'''
===============================================================================
ACADEMIC INTEGRITY STATEMENT
    I have not used source code obtained from any other unauthorized
    source, either modified or unmodified. Neither have I provided
    access to my code to another. The project I am submitting
    is my own original work.
===============================================================================
'''