% function [location] = loc(x,y)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% ENGR 133 
% Program Description 
% Uses a function to locate what room the camera is in based on
% coordinates
%
% Function Call
% locate = loc(x,y)
%
% Input Arguments (x,y)
% x=3, y=20
% x=-2, y=4
% x=-7, y=22
% x=-6, y=-2
% x=15, y=10
%
% Output Arguments [location]
% Camera location: Lobby
% Camera location: Observatory
% Camera location: Office
% Camera location: Outside of building
% Camera location: Outside of building
%
% Assignment Information
%   Assignment:     Ma3_Task1
%   Team ID:        LC1-04
%   Contributor:    Nolan Hays, haysn@purdue.edu
%                   Jackson Bitterolf, jbittero@purdue.edu
%                   Ayush Viswanathan, viswan11@purdue.edu
%                   Roshan Sundar, rmsundar@purdue.edu
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
% User enters the x and y coordinates (commented out for publication)
%x = input('Enter the x-coordinate: ');
%y = input('Enter the y-coordinate: ');

% Initialize x and y for publication
x = 3;
y = 20;

% Call the function with x and y as inputs
locate = loc(x,y);

%% ____________________
%% USER-DEFINED FUNCTION
function [location] = loc(x,y)  % Define the function to locate the camera

d = sqrt((x^2)+(y^2));          % Use the distance formula to calculate how far the point is from the origin (center of observatory)

if d < 5    % Is the point within 5m of the center of the observatory (which has a radius of 5m)?
    location = 'Observatory';
elseif x > -1 && x < 11 && y > 17 && y < 23     % Is the point in the range of the lobby?
    location = 'Lobby';
elseif x < -1 && x > -11 && y > 17 && y < 23    % Is the point in the range of the office?
    location = 'Office';
elseif x > -11 && x < 11 && y > 5 && y < 17     % Is the point in the range of the exhibit hall?
    location = 'Exhibit Hall';
elseif d > 5 && x <= 5 && x >4 && y > -3 && y < 3   % Is the point in the range of the vestibule (and not in the radius of the observatory)?
    location = 'Vestibule';
else                                            % If the point is anywhere else, it must be outside of the building.
    location = 'Outside of building';
end

% Print the camera's location
fprintf('Camera location: %s', location)
fprintf('\n')

end


%% ____________________
%% COMMAND WINDOW OUTPUT
% Enter the x-coordinate: 3
% Enter the y-coordinate: 20
% Camera location: Lobby


%% ____________________
%% ACADEMIC INTEGRITY STATEMENT
% I have not used source code obtained from any other unauthorized
% source, either modified or unmodified.  Neither have I provided
% access to my code to another. The project I am submitting
% is my own original work.