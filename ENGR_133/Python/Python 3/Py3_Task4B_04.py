
'''
===============================================================================
ENGR 133 Fa 2020

Assignment Information
	Assignment:     Py3 Task4B
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

import math as m 

import Py3_Task3_factorial_04 as f 

# Input
x = float(input('Enter the value of x: '))  
n = float(input('Enter the target error threshold: ')) 

tValue = 0 
aValue=round(m.pow(m.e,x),2) 
numTerms = 0 

# Run loop until approx vlue is in threshold
while(True): 
    tValue +=((m.pow(x,numTerms))/f.MyFactorial(numTerms)) 
    numTerms +=1 
    if(n > (abs((tValue-aValue)/(aValue))*100)): 
        break 

# Output results
print(f'\nTarget error threshold: {n}%') 

print(f'Actual value: {aValue}')  

print(f'Terms needed: {numTerms}') 

print(f'Approximate value: {round(tValue,2)}') 

'''
===============================================================================
ACADEMIC INTEGRITY STATEMENT
    I have not used source code obtained from any other unauthorized
    source, either modified or unmodified. Neither have I provided
    access to my code to another. The project I am submitting
    is my own original work.
===============================================================================
'''



