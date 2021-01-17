
'''
===============================================================================
ENGR 133 Fa 2020

Assignment Information
	Assignment:     Py3 Task4A
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


n=int(input('Enter the value of n: ')) 
x=int(input('Enter the value of x: ')) 

tValue=0 
aValue=round(m.pow(m.e,x),2) 

# Calculate approximate value
for i in range (0,n+1):  
    tValue +=((m.pow(x,i))/f.MyFactorial(i)) 

# Output results
print(f'Approximate value: {round(tValue,2)}') 
print(f'Actual value: {aValue}') 

error=round(100*((tValue-aValue)/(aValue)),1) 
print(f'Error: {error}%') 

'''
===============================================================================
ACADEMIC INTEGRITY STATEMENT
    I have not used source code obtained from any other unauthorized
    source, either modified or unmodified. Neither have I provided
    access to my code to another. The project I am submitting
    is my own original work.
===============================================================================
'''



