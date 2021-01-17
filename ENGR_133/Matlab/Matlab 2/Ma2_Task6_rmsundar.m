%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% ENGR 133 
% Program Description: 
%
% Assignment Information
%   Assignment:     Ma2 Task6
%   Author:         Roshan Sundar, rmsundar
%   Team ID:        LC1-04
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%% ____________________
%% INITIALIZATION
max_a = 1000000;
a = 0;
p = 11000;
r = 0.02;
n = 1;
t = 0;

%% ____________________
%% CALCULATIONS
while a < max_a
    t = t + 1;
    a = p * (1+(r/n))^(n*t);
end

%% ____________________
%% OUTPUTS
fprintf('The savings account would exceed $1 million after %d years.', t)

%% ____________________
%% ACADEMIC INTEGRITY STATEMENT
% I have not used source code obtained from any other unauthorized
% source, either modified or unmodified.  Neither have I provided
% access to my code to another. The project I am submitting
% is my own original work.