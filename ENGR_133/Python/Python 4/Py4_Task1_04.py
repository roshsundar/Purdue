
'''
===============================================================================
ENGR 133 Fa 2020

Assignment Information
	Assignment:     Py4 Task1
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

# Get required variables
year = 365.242199
file = open('Py4_Task1_output.txt', 'w')
lastName = input('Enter your last name: \n')
firstName = input('Enter your first name: \n')
age = input('Enter your age in whole years: \n')
age = float(age)
lastBday = input('Enter the days elapsed since your last birthday: \n')
lastBday = float(lastBday)

# Calculation
age = age + (lastBday/year)
ageSeconds = int(age * 365 * 24 * 3600)

# Output
file.write(firstName + " ")
file.write(lastName)
file.write(f'\n You are {age} years old.')
file.write(f'\n You are {ageSeconds} seconds old.')
file.close()


'''
===============================================================================
ACADEMIC INTEGRITY STATEMENT
    I have not used source code obtained from any other unauthorized
    source, either modified or unmodified. Neither have I provided
    access to my code to another. The project I am submitting
    is my own original work.
===============================================================================
'''



