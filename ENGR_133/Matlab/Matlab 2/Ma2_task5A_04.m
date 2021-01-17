%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% ENGR 133 
% Program Description: 
%
% Assignment Information
%   Assignment:     Ma2 Task5A
%   Author:         Roshan Sundar, rmsundar
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
n = input('input n: ');
x = input('input x: ');
tValue = 0;

%% ____________________
%% CALCULATIONS
aValue = round(exp(x),2);

for i = 0:n
    tValue = tValue + (x^i)/factorial(i);
end
tValue = round(tValue, 2);
error = round(100*((tValue-aValue)/(aValue)),1);
%% ____________________
%% OUTPUTS
fprintf('Approximate value: %.2f\n', tValue)
fprintf('Actual value: %.2f\n', aValue)
fprintf('Error: %.2f\n', error)
%% ____________________
%% ACADEMIC INTEGRITY STATEMENT
% I have not used source code obtained from any other unauthorized
% source, either modified or unmodified.  Neither have I provided
% access to my code to another. The project I am submitting
% is my own original work.