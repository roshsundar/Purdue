%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% ENGR 133 
% Program Description: 
%
% Assignment Information
%   Assignment:     Ma2 Task7
%   Author:         Roshan Sundar, rmsundar
%   Team ID:        LC1-04
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%% ____________________
%% INITIALIZATION
v = [10 5 1 8 -9 0 2 3];

%% ____________________
%% CALCULATIONS
v1 = v;
descend = zeros(1, length(v));
for i=1:length(v1)
    [M,I] = max(v1);
    descend(i) = M;
    v1(I) = min(v1) - 1;
end

v2 = v;
ascend = zeros(1, length(v));
for i=1:length(v2)
    [M,I] = min(v2);
    ascend(i) = M;
    v2(I) = max(v2) + 1;
end

%% ____________________
%% OUTPUTS
disp('Vector sorted in descending order:')
disp(descend)
disp('Vector sorted in ascending order:')
disp(ascend)

%% ____________________
%% ACADEMIC INTEGRITY STATEMENT
% I have not used source code obtained from any other unauthorized
% source, either modified or unmodified.  Neither have I provided
% access to my code to another. The project I am submitting
% is my own original work.