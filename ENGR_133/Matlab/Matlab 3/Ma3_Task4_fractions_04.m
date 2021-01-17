function [f1,f2,f3] = Ma3_Task4_fractions_04(ss,sw,sa)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% ENGR 133 
% Program Description 
%replace this text with your program decription as a comment
%
% Function Call
%replace this text with a comment that states the function call
%
% Input Arguments
%replace this text with a commented list of the input arguments
%
% Output Arguments
%replace this text with a commented list of the output arguments
%
% Assignment Information
%   Assignment:     Ma3_Task 4
%   Author:         
%   Team ID:        LC1-04 
%  	Contributor:    Ayush Viswanathan, Roshan Sundar, Jackson Bitterolf,
%  	Nolan Hays
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

    f1 = .5 * (1 + (ss/sw) - sqrt(1 + (ss/sw)^2 + 2*(ss/sw)*sind(sa)));
    f2 = .5 * (sqrt(1 + (ss/sw)^2 + 2*(ss/sw)*sind(sa)) + sqrt(1 + (ss/sw)^2 - 2*(ss/sw)*sind(sa)) - 2*(ss/sw));
    f3 = .5 * (1 + (ss/sw) - sqrt(1 + (ss/sw)^2 - 2*(ss/sw)*sind(sa)));
end

%% ____________________
%% CALCULATIONS



%% ____________________
%% FORMATTED TEXT & FIGURE DISPLAYS



%% ____________________
%% COMMAND WINDOW OUTPUT



%% ____________________
%% ACADEMIC INTEGRITY STATEMENT
% I have not used source code obtained from any other unauthorized
% source, either modified or unmodified.  Neither have I provided
% access to my code to another. The project I am submitting
% is my own original work.