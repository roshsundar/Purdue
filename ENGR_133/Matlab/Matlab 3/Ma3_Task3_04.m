%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% ENGR 133 
% Program Description: Create an exercise schedule
%
% Assignment Information
%   Assignment:     Ma3 Task3
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
% initialize schedule matrix with 0 in correct dimensions
schedule = zeros(4,7);

%% ____________________
%% CALCULATIONS
index = 1;
% loop over each element 
for i = 1:size(schedule,1)
    for j = 1:size(schedule,2)
        % if element in column 7
        if j == 7
            schedule(i,j) = 0;
        % if element in column 2
        elseif j == 2
            schedule(i,j) = 60;
        % if element index even
        elseif mod(index, 2) == 0
            schedule(i,j) = 45;
        % if element index odd
        else
            schedule(i,j) = 30;
        end
        index = index + 1;   
    end
end

disp_fun_task3(schedule)
%% ____________________
%% OUTPUTS
function disp_fun_task3(sched)
    disp("The exercise plan is:")
    % Add day headers above each column
    array = ["M" "T" "W" "Th" "F" "Sa" "Su"; sched];
    disp(array)
end
%% ____________________
%% ACADEMIC INTEGRITY STATEMENT
% I have not used source code obtained from any other unauthorized
% source, either modified or unmodified.  Neither have I provided
% access to my code to another. The project I am submitting
% is my own original work.