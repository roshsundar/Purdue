# -*- coding: utf-8 -*-
'''
===============================================================================
ENGR 133 Fa 2020

Assignment Information
	Assignment:     Py2 Task2
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
temperature = float(input('What is the temperature?: ')) 
hydration = float(input('What is the hydration?: ')) 

  

def tempHyd(temp, hyd):  

    if (temp > 14 or hyd > 60):  
        print('Danger')  

        if(temp > 14):  
            print('High Temperature') 
        else:  
            print('High Hydration') 

    elif (10 < temp < 14 and 55 < hyd < 60):  
        print('Normal') 

    else:  
        print('Warning')  

        if(temp < 10):  
            print('Low Temperature') 
        else:  
            print('Low Hydration') 

 
tempHyd(temperature,hydration) 

'''
===============================================================================
ACADEMIC INTEGRITY STATEMENT
    I have not used source code obtained from any other unauthorized
    source, either modified or unmodified. Neither have I provided
    access to my code to another. The project I am submitting
    is my own original work.
===============================================================================
'''