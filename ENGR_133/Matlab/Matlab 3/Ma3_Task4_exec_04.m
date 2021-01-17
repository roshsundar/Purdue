%function replace this text with your function definition line
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
slat_spacing = 50; %mm
slat_width = 60; %mm
absorptivity_constant = .76;
shadow_angle = 45; %degrees
blind_setting = [30,45,60]; %degrees

for i = 1:length(blind_setting)
    exec(slat_spacing,slat_width,absorptivity_constant,shadow_angle,blind_setting(i),i);
end


%% ____________________
%% CALCULATIONS
function exec(ss,sw,ac,vsa,sa,index)
    [fa1,fa2,fa3] = Ma3_Task4_fractions_04(ss,sw,sa);
    av = Ma3_Task4_absorb_04(ss,sw,ac,vsa,sa,fa1,fa2,fa3);
    tv = Ma3_Task4_transmission_04(ss,sw,ac,vsa,sa,fa1,fa2,fa3);
    fprintf('The transmission value for Blind %d at %d is %f.\n',index,sa,tv);
    fprintf('The absorption value for Blind %d at %d is %f.\n',index,sa,av)
end


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