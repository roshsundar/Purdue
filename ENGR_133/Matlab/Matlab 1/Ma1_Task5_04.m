%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% ENGR 133 
% Program Description: 
%
% Assignment Information
%   Assignment:     Ma_ Task_
%   Author:         Roshan Sundar, rmsundar@purdue.edu
%   Team ID:        LC1-04
%  	Contributor:    Ayush Viswanathan, Jackson Bitterolf, Nolan Hays
%   My contributor(s) helped me:	
%     [ ] understand the assignment expectations without
%         telling me how they will approach it.
%     [ ] understand different ways to think about a solution
%         without helping me plan my solution.
%     [ ] think through the meaning of a specific error or
%         bug present in my code without looking at my code.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%% ____________________
%% INITIALIZATION
X = [-50:0.1:50];

%% ____________________
%% CALCULATIONS
Y = X - X.^3/factorial(3) + X.^5/factorial(5) - X.^7/factorial(7);

%% ____________________
%% OUTPUTS
plot(X,Y)
xlabel('Angle (rad)')
ylabel('Value of Sine Approximation')
title('Taylor Series Approximation of the Sine Function')

%% ____________________
%% ACADEMIC INTEGRITY STATEMENT
% I have not used source code obtained from any other unauthorized
% source, either modified or unmodified.  Neither have I provided
% access to my code to another. The project I am submitting
% is my own original work.