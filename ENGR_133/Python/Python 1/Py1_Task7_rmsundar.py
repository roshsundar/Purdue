# -*- coding: utf-8 -*-
'''
===============================================================================
ENGR 133 Fa 2020

Assignment Information
	Assignment:     Py1 Task7
	Author:         Roshan Sundar, rmsundar@purdue.edu
	Team ID:        LC1-04
===============================================================================
'''
import math as m
import pandas as pd
import numpy as np

First_Inductance = float(input("Enter first inductance [\u03BCH]: "))
Second_Inductance = m.sqrt(3.14) * m.pi

Parallel_Inductance = 1/((1/First_Inductance) + (1/Second_Inductance))
Series_Inductance = First_Inductance + Second_Inductance

data = np.array([['Parallel',f'{round(First_Inductance, 1)} \u03BCH', f'{round(Second_Inductance, 1)} \u03BCH', f'{round(Parallel_Inductance, 1)} \u03BCH'],
                 ['Series',f'{round(First_Inductance, 1)} \u03BCH', f'{round(Second_Inductance, 1)} \u03BCH', f'{round(Series_Inductance, 1)} \u03BCH']
                 ])
table = pd.DataFrame(data,['', ''] ,['Type of Inductance', 'First Inductance', 'Second Inductance', 'Equivalent Inductance'])
print(table)
# table reference https://pandas.pydata.org/pandas-docs/stable/reference/api/pandas.DataFrame.html