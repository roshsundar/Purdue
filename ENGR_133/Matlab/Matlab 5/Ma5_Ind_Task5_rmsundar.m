%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% ENGR 133 
% Program Description: 
%
% Assignment Information
%   Assignment:     Ma5 Task5
%   Team ID:        LC1-04
%  	Contributor:    Roshan Sundar
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%% ____________________
%% INITIALIZATION
data = csvread('Data_speaker_volume_power.csv', 2,0);

%% ____________________
%% CALCULATIONS
power = data(:,1);
SPK3_volume = data(:,2);
SPK4_volume = data(:,3);

%% ____________________
%% OUTPUTS
%Linear
subplot(2,2,1)
plot(power, SPK3_volume)
hold on
plot(power, SPK4_volume)
title('Speaker volume vs Power - Linear Plot')
xlabel('Power (mW)')
ylabel('Volume (dB)')
legend('SPK3', 'SPK4','Location','southeast')
hold off

%Semilogx
subplot(2,2,2)
semilogx(power, SPK3_volume)
hold on
semilogx(power, SPK4_volume)
title('Speaker volume vs Power - Semilogx Plot')
xlabel('Power (mW)')
ylabel('Volume (dB)')
legend('SPK3', 'SPK4','Location','southeast')
hold off

%Semilogy
subplot(2,2,3)
semilogy(power, SPK3_volume)
hold on
semilogy(power, SPK4_volume)
title('Speaker volume vs Power - Semilogy Plot')
xlabel('Power (mW)')
ylabel('Volume (dB)')
legend('SPK3', 'SPK4','Location','southeast')
hold off

%Loglog
subplot(2,2,4)
loglog(power, SPK3_volume)
hold on
loglog(power, SPK4_volume)
title('Speaker volume vs Power - Loglog Plot')
xlabel('Power (mW)')
ylabel('Volume (dB)')
legend('SPK3', 'SPK4','Location','southeast')
hold off

%Overall
sgtitle('Speaker volume vs Power for SPK3 & SPK4, Displayed in Various Scales')

%% ____________________
%% Analysis
% The best fit function is a logarithm. The charts show a logarithmic
% curved relationship in the various plots, including the linear and log
% scaled plots.

%% ____________________
%% ACADEMIC INTEGRITY STATEMENT
% I have not used source code obtained from any other unauthorized
% source, either modified or unmodified.  Neither have I provided
% access to my code to another. The project I am submitting
% is my own original work.