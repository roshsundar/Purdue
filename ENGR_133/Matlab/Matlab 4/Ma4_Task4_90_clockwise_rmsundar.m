%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% ENGR 133 
% Program Description: Rotate image 90 degrees clockwise
%
% Assignment Information
%   Assignment:     Ma4 Task4
%   Team ID:        LC1-04
%  	Contributor:    Roshan Sundar
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%% ____________________
%% Function
function out_img = Ma4_Task4_90_clockwise_rmsundar(in_img)
    out_img = in_img;
    %Turn in_img -90o by running 3 X 90o
    for i=1:3
        out_img = Ma4_Task4_90_counterclockwise_rmsundar(out_img);
    end
end

%% ____________________
%% ACADEMIC INTEGRITY STATEMENT
% I have not used source code obtained from any other unauthorized
% source, either modified or unmodified.  Neither have I provided
% access to my code to another. The project I am submitting
% is my own original work.