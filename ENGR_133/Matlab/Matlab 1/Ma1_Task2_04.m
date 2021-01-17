%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% ENGR 133 
% Program Description: 
%
% Assignment Information
%   Assignment:     Ma1 Task2
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
%% PART A

d = 6; % meters
h = 10; % meters

capacity = pi * h * (d/2)^2; % meters^3
capacity = capacity * 264.172052; % gallons

disp('The capacity in U.S. gallons is:');
capacity

%% ____________________
%% PART B

d = 4; % meters
h = 9; % meters

capacity = pi * h * (d/2)^2; % meters^3
capacity = capacity * 264.172052; % gallons
capacity = round(capacity);
fprintf('The capacity is %i U.S. gallons.\n', capacity);
fprintf('The tank has a diameter of %0.1f ft and is %0.1f ft tall. \n',d,h);

%% ____________________
%% ACADEMIC INTEGRITY STATEMENT
% I have not used source code obtained from any other unauthorized
% source, either modified or unmodified.  Neither have I provided
% access to my code to another. The project I am submitting
% is my own original work.