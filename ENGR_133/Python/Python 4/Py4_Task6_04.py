
'''
===============================================================================
ENGR 133 Fa 2020

Assignment Information
	Assignment:     Py4 Task6
	Author:         Roshan Sundar, rmsundar@purdue.edu
	Team ID:        LC1-04
===============================================================================
'''
infile_name = input("What is the input file name: ")
outfile_name = input("What is the output file name: ")

infile = open(infile_name, 'r')
outfile = open(outfile_name, 'w')
lines = infile.readlines()
for i in range(len(lines)):
    outfile.write(f'Step {i+1}: {lines[i]}')

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



