
'''
===============================================================================
ENGR 133 Fa 2020

Assignment Information
	Assignment:     Py4 Task3
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

# Open necessary files
inFile = open('Py4_Task3_input.txt', 'r')
outFile = open('Py4_Task3_output.txt', 'w')

listString = []
splitList = []
 
x = 0

# Extract each line in List and String form
for line in inFile:
    if x > 0:
        str = line
        listString.append(str)
        strList = str.split()
        splitList.append(strList)
    x += 1

# Output the String & List version of each line in the proper format
for i in range(len(listString)):
    outFile.write(listString[i])
    outFile.write("['" + "', '".join(splitList[i]) + "']\n")
    
# Close files
inFile.close()
outFile.close()
    

'''
===============================================================================
ACADEMIC INTEGRITY STATEMENT
    I have not used source code obtained from any other unauthorized
    source, either modified or unmodified. Neither have I provided
    access to my code to another. The project I am submitting
    is my own original work.
===============================================================================
'''



