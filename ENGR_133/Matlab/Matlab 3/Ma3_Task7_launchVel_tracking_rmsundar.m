%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% ENGR 133 
% Program Description Calculate velocity of a rocket over a time interval
% given some data
%
% Assignment Information
%   Assignment:     Ma3 Task7
%   Author:         Name, login@purdue.edu
%   Team ID:        LC1-04
%  	Contributor:    Roshan Sundar
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% ____________________
%% INITIALIZATION
Data = csvread('Data_RDAS.csv',1,0);
Time = Data(:,1);
Altitude = Data(:,2);
Accel = Data(:,3);

%% ____________________
%% CALCULATIONS
Velocity = [0];
for t=2:numel(Time)
    currentVel = 0;
    for k=2:t
        currentVel = currentVel +((Time(k)-Time(k-1))*(Accel(k)+Accel(k-1))/2);
    end
    Velocity = [Velocity; currentVel];
end

[maxVel, maxVel_i] = max(Velocity);
maxVel_time = Time(maxVel_i);
%% ____________________
%% FIGURE DISPLAY
subplot(3,1,1)
plot(Time, Accel)
title('Acceleration vs Time of Rocket')
xlabel('Time(s)')
ylabel('Acceleration(ft/s^2)')

subplot(3,1,2)
plot(Time, Velocity)
title('Velocity vs Time of Rocket')
xlabel('Time(s)')
ylabel('Velocity(ft/s)')

subplot(3,1,3)
plot(Time, Altitude)
title('Altitude vs Time of Rocket')
xlabel('Time(s)')
ylabel('Altitude(ft)')

%% ____________________
%% TEXT DISPLAY
fprintf('The maximum launch velocity is %0.4f ft/s and occurs at %0.3f s\n', maxVel, maxVel_time)

%% ____________________
%% ACADEMIC INTEGRITY STATEMENT
% I have not used source code obtained from any other unauthorized
% source, either modified or unmodified.  I have not provided
% access to my code to anyone in any way. The script I am 
% submitting is my own original work.