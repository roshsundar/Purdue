
'''
===============================================================================
ENGR 133 Fa 2020

Assignment Information
	Assignment:     Py3 Task3
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

import Py3_Task3_factorial_04 

fact = input('Number whose factorials will be evaluated: ') 
l = fact.split() 

# Calculate factorial for each element
for x in range(0,len(l)): 
    l[x] = int(l[x]) 
    f = Py3_Task3_factorial_04.MyFactorial(l[x]) 
    # Test for negativity
    if(f == -1): 
        print('Error: factorial routine requires positive integers.') 
    else: 
        print(f'The factorial of {l[x]} is {f}.') 

'''
===============================================================================
ACADEMIC INTEGRITY STATEMENT
    I have not used source code obtained from any other unauthorized
    source, either modified or unmodified. Neither have I provided
    access to my code to another. The project I am submitting
    is my own original work.
===============================================================================
'''



