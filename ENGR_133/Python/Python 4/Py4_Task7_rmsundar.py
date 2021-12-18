
'''
===============================================================================
ENGR 133 Fa 2020

Assignment Information
	Assignment:     Py4 Task7
	Author:         Roshan Sundar, rmsundar@purdue.edu
	Team ID:        LC1-04

===============================================================================
'''

infile_name = input("What is the name of txt file: ")
searchword = input("What is the search word: ")
infile = open(infile_name, 'r')

text = infile.read()
words = text.split()

searchCount = 0
totalCount = 0
for word in words:
    word_new = ""
    for c in word:
        if c.isalpha():
            word_new +=c
            
    if word_new.lower() == searchword.lower():
        searchCount += 1
    totalCount += 1

percentage = (searchCount/totalCount)*100

print(f'The search word occurred {percentage:.2f}% of the time.')

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



