%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% ENGR 133 
% Program Description: 
%
% Assignment Information
%   Assignment:     Ma2 Task5B
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
x = input('Enter the value of x: ');
n = input('Enter the target error threshold: ');

tValue = 0;
aValue = round(exp(x),2);
numTerms = 0;
%% ____________________
%% CALCULATIONS
while 1
    tValue = tValue + (x^numTerms)/factorial(numTerms);
    numTerms = numTerms + 1;
    if (n > (abs((tValue-aValue)/(aValue))*100))
        break
    end
end
tValue = round(tValue,2);
%% ____________________
%% OUTPUTS
fprintf('Target error threshold: %d%%\n', n);
fprintf('Actual value: %.2f\n', aValue);
fprintf('Terms needed: %d\n', numTerms);
fprintf('Approximate value: %.2f\n', tValue);

%% ____________________
%% ACADEMIC INTEGRITY STATEMENT
% I have not used source code obtained from any other unauthorized
% source, either modified or unmodified.  Neither have I provided
% access to my code to another. The project I am submitting
% is my own original work.