
'''
===============================================================================
ENGR 133 Fa 2020

Assignment Information
	Assignment:     Py4 Task4
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
# Open files
infile=open('Py4_Task4_input.txt','r')
outfile=open('Py4_Task4_output.txt','w')

# Read input file
lines=infile.readlines()

# Create lists to be used later
list1=[]
listYears=[]
listMonths=[]

# Dictionary of months and respective index
dic={1:'January',2:'February',3:'March',4:'April',5:'May',6:'June',7:'July',8:'August',9:'September',10:'October',11:'November',12:'December'}

# Assistive function to get key from dictionary given a value
def getKey(val):
    for key, value in dic.items():
        if val == value:
            return key
    return "key doesnt exist"

# Sort dates into past, present, future
def Sort_Dates(): 
    countFuture=0
    countPast=0
    for i in lines:
        list1.append(i)
    for i in list1:
        listYears.append(i.split()[1])
    for i in list1:
        listMonths.append(i.split()[0])
    
    for i in range(len(listYears)):
        listYears[i]=int(listYears[i])
        if listYears[i] <= 2020:
            countPast+=1
        if listYears[i]>2020:
            countFuture+=1
    # Determine if month is future or present
    outfile.write(f'Future months: {countFuture} \n')
    for i in range(len(listYears)):
        listYears[i]=int(listYears[i])
        if listYears[i]> 2020:
            outfile.write(f'{list1[i]} \n')
        elif listYears[i]==2020:
            if (getKey(listMonths[i])== 10):
                outfile.write(f'Present Month: {listMonths[i]} \n')
    # Determine if month is past or present
    outfile.write(f'Past months: {countPast} \n')
    for i in range(len(listYears)):
        listYears[i]=int(listYears[i])
        if listYears[i]<=2020:
            outfile.write(f'{list1[i]} \n')
        elif listYears[i]==2020:
            if (getKey(listMonths[i])== 10):
                outfile.write(f'Present Month: {listMonths[i]} \n')

# Call main fucntion
Sort_Dates()

# Close files
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



