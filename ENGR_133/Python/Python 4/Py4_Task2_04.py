
'''
===============================================================================
ENGR 133 Fa 2020

Assignment Information
	Assignment:     Py4 Task2
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

# Open necessary files and read input content
import math as m
infile=open('Py4_Task2_input.txt','r')
outfile=open('Py4_Task2_output.txt','w')
lines= infile.readlines()
nums=[]

# Extract scores into list
for i in lines:
    nums.append(float(i.split()[1]))
    
# Calculate average & standard deviation
def Avg_Std():
    x=sum(nums)
    mean=x/(len(nums))
    var=0
    std=0
    
    for i in nums:
        var += (i-mean)**2
    var= float(var/len(nums))
    std= m.sqrt(var)
    
    return round(mean,2), round(std,2)

# Find mx & min
def Hi_Lo():
    maxNums=round(max(nums),2)
    minNums=round(min(nums),2)
    return maxNums, minNums

# Call functions
me,std= Avg_Std()
h,l=Hi_Lo()

# Output
outfile.write('Exam 1: \n')
outfile.write(f'Average = {me}')
outfile.write(f'Standard Deviation = {std} \n')
outfile.write(f'High Score = {h} \n')
outfile.write(f'Low Score = {l}')
 
infile.close()
outfile.close()


'''
===============================================================================
ACADEMIC INTEGRITY STATEMENT
    I have not used source code obtained from any other unauthorized
    source, either modified or unmodified. Neither have I provided
    access to my code to another. The project I am submitting
    is my own original work.
===============================================================================
'''



