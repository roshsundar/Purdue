%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% ENGR 133 
% Program Description: Convert image to grayscale & invert it
%
% Assignment Information
%   Assignment:     Ma4 Task5
%   Team ID:        LC1-04
%  	Contributor:    Roshan Sundar
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%% ____________________
%% INITIALIZATION
orig_img = imread('block.png');

%% ____________________
%% CALCULATIONS
%Calculate grayscale
redVals = orig_img(:,:,1);
greenVals = orig_img(:,:,2);
blueVals = orig_img(:,:,3);

gray_img = 0.2126*double(redVals) + 0.7152*double(greenVals) + 0.0722*double(blueVals);
gray_img = uint8(gray_img);

invert_img = 255 - gray_img;
invert_img = uint8(invert_img);

%% ____________________
%% OUTPUTS
figure(1)
imshow(orig_img)
title('Original Image')

figure(2)
imshow(gray_img)
title('Grayscale Image')

figure(3)
imshow(invert_img)
title('Inverted Image')

%% ____________________
%% ACADEMIC INTEGRITY STATEMENT
% I have not used source code obtained from any other unauthorized
% source, either modified or unmodified.  Neither have I provided
% access to my code to another. The project I am submitting
% is my own original work.