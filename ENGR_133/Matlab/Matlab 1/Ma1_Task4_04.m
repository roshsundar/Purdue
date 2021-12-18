%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% ENGR 133 
% Program Description: 
%
% Assignment Information
%   Assignment:     Ma1 Task4
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
%% INITIALIZATIONS
b = 1300; %meters
A = 25; %degrees
C = 37; %degrees
 
 
%% ____________________
%% CALCULATIONS
 
B = 180 - A - C; %degrees
a = b * (sind(A) / sind(B)); %meters
a = round(a)
c = b * (sind(C) / sind(B)); %meters
c = round(c)
 
%% ____________________
%% OUTPUTS
 
fprintf('Distance b: %d \n', b)
fprintf('Angle A: %d \n', A)
fprintf('Angle C: %d \n', C)
fprintf('Distance a: %d meters\n', a)
fprintf('Distance c: %d meters\n', c)
fprintf('Angle B: %.1f degrees\n', B)

%% ____________________
%% ACADEMIC INTEGRITY STATEMENT
% I have not used source code obtained from any other unauthorized
% source, either modified or unmodified.  Neither have I provided
% access to my code to another. The project I am submitting
% is my own original work.