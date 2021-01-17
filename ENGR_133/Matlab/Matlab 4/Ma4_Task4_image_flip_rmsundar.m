%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% ENGR 133 
% Program Description: Rotate image based on user input
%
% Assignment Information
%   Assignment:     Ma4 Task4
%   Team ID:        LC1-04
%  	Contributor:    Roshan Sundar
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%% ____________________
%% INITIALIZATION
% read image
orig_img = imread('block.png');

% get user choice on rotation
choice = menu('Select a rotation','90o cw', '90o ccw', '180o/flipped');
%choice = 2;

%% ____________________
%% OUTPUTS
figure(1)
imshow(orig_img)
title('Original Image')

img_disp = [];
if choice==1
    img_disp = Ma4_Task4_90_clockwise_rmsundar(orig_img);
    figure(2)
    imshow(img_disp)
    title('Image rotated 90 degrees')
elseif choice==2
    img_disp = Ma4_Task4_90_counterclockwise_rmsundar(orig_img);
    figure(2)
    imshow(img_disp)
    title('Image rotated -90 degrees')
elseif choice==3
    img_disp = Ma4_Task4_180_flipped_rmsundar(orig_img);
    figure(2)
    imshow(img_disp)
    title('Image rotated 180 degrees')
end
%% ____________________
%% ACADEMIC INTEGRITY STATEMENT
% I have not used source code obtained from any other unauthorized
% source, either modified or unmodified.  Neither have I provided
% access to my code to another. The project I am submitting
% is my own original work.