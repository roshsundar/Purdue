
'''
===============================================================================
ENGR 133 Fa 2020

Assignment Information
	Assignment:     Py4 Task5
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

# Function to calculate concentration
def Absorb_Calc(A, ep, b):
    return A/(ep*b)

# Open file and read content
infile = open('Py4_Task5_input.txt', 'r')
lines = infile.readlines()

# Extract necessary info from file
name = lines[0]
b = float(lines[1])
ep = float(lines[2])
A_list = []
for i in range(3, len(lines)):
    A_list.append(float(lines[i]))

# Calculate concentration from each absorbancy
c_list = []
for A in A_list:
    c_list.append(round(Absorb_Calc(A, ep, b), 7))
    
# Print Output
print(name)
for c in c_list:
    print(f'{c:.7f}')

infile.close()

'''
===============================================================================
ACADEMIC INTEGRITY STATEMENT
    I have not used source code obtained from any other unauthorized
    source, either modified or unmodified. Neither have I provided
    access to my code to another. The project I am submitting
    is my own original work.
===============================================================================
'''



