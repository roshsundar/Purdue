
'''
===============================================================================
ENGR 133 Fa 2020

Assignment Information
	Assignment:     Py3 Task2
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

# define function that calculates factorial
def MyFactorial(n): 
    x = n 
    fact = 1 
    if(x < 0): 
        return -1 
    elif(x==0): 
        return 1 
    else: 
        while x > 0: 
            fact *= x 
            x-=1 
        return fact

num = int(input('Nth term of Factorial: ')) 
f = MyFactorial(num)
# Test if factorial is negative (which it should not be)
if(f == -1): 
    print('Error[negative input]') 
else: 
    print(f'The Factorial of {num} is {f}.')


'''
===============================================================================
ACADEMIC INTEGRITY STATEMENT
    I have not used source code obtained from any other unauthorized
    source, either modified or unmodified. Neither have I provided
    access to my code to another. The project I am submitting
    is my own original work.
===============================================================================
'''



