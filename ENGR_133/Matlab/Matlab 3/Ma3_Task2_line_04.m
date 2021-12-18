%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% ENGR 133 
% Program Description: 
%
% Assignment Information
%   Assignment:     Ma3 Task2
%   Team ID:        LC1-04
%  	Contributor:    Ayush Viswanathan, Jackson Bitterolf, Nolan Hays,
%  	Roshan Sundar
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
% first point
p1_x = 4; % inches
p1_y = 4; % inches

% second point
p2_x = 5; % inches
p2_y = 5; % inches

%% ____________________
%% CALCULATIONS
% calculate length of line between the 2 points in inches
L_in = sqrt(((p2_x - p1_x)^2) + ((p2_y - p1_y)^2)); % inches
% convert to cm using function
L_cm = Ma3_Task2_INtoCM_04(L_in); % cm
%% ____________________
%% OUTPUTS
% display lengths in inches and cm
fprintf('Length in inches: %f\n', L_in)
fprintf('Length in cm: %f\n', L_cm)

% Test Case 1
% Input: p1_x = 4, p1_y = 4, p2_x = 6, p2_y = 4
% Output: L_in = 2, L_cm = 5.08

% Test Case 2
% Input: p1_x = 4, p1_y = 4, p2_x = 5, p2_y = 5
% Output: L_in = 1.414214, L_cm = 3.592102

%% ____________________
%% ACADEMIC INTEGRITY STATEMENT
% I have not used source code obtained from any other unauthorized
% source, either modified or unmodified.  Neither have I provided
% access to my code to another. The project I am submitting
% is my own original work.