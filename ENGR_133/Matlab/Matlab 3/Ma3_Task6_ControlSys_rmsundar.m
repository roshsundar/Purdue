%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% ENGR 133 
% Program Description: 
%
% Assignment Information
%   Assignment:     Ma3 Task6
%   Team ID:        LC1-04
%  	Contributor:    Roshan Sundar
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%% ____________________
%% INITIALIZATION
data = csvread('LaneWidth_TrafficSpeed.csv', 3, 0);
mileMarker = data(:,1);
laneWidth = data(:,2);

%% ____________________
%% CALCULATIONS
%a
[LW_max, i_MM] = max(laneWidth);
MM_max = mileMarker(i_MM);

[LW_min, i_MM] = min(laneWidth);
MM_min = mileMarker(i_MM);

%b
MM_range = [];
for i=1:numel(laneWidth)
    if laneWidth(i) < 10
        MM_range = [MM_range; i];
    end
end
P_i = min(MM_range);
Q_i = max(MM_range);
P = mileMarker(P_i);
Q = mileMarker(Q_i);

%c
speed = 60; %mph
sp1 = (P-145)/speed; %hours
sp2 = (Q-P)/speed; %hours
sp3 = (146-Q)/speed; %hours

%d
plot(laneWidth, mileMarker)
% the number of data points above 10 does not seem statistically
% significant

%e
count = 0;
for i=min(MM_range):max(MM_range)
    if laneWidth(i) > 10
        count = count + 1;
    end
end
percentage = count/(Q_i-P_i+1);

%f
% My answer does not change since less than 0.5% of the values are above 10

%% ____________________
%% OUTPUTS
fprintf('The maximum lane width is %0.4f at mile marker %0.4f\n', LW_max, MM_max)
fprintf('The minimum lane width is %0.4f at mile marker %0.4f\n', LW_min, MM_min)
fprintf('The mile marker Q is %0.4f, the mile marker P is %0.4f\n', Q, P)
fprintf('The percentage of points between P and Q where lane width exceeds 10 is %0.4f\n', percentage)

%% ____________________
%% ACADEMIC INTEGRITY STATEMENT
% I have not used source code obtained from any other unauthorized
% source, either modified or unmodified.  Neither have I provided
% access to my code to another. The project I am submitting
% is my own original work.