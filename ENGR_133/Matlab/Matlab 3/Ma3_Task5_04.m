%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% ENGR

%% 
% Assignment Information
%   Assignment:     Ma3_Task5
%   Author:         Team4
%   Team ID:        01
%  	Contributor:    
%                   Jackson Bitterolf: jbittero
%                   Ayush Viswanathan: viswan11
%                   Nolan Hays: haysn
%                   Roshan Sundar: rmsundar
%   My contributor(s) helped me:	
%     [ ] understand the assignment expectations without
%         telling me how they will approach it.
%     [ ] understand different ways to think about a solution
%         without helping me plan my solution.
%     [ ] think through the meaning of a specific error or
%         bug present in my code without looking at my code.

%did you complete the assignment information? delete this line if yes
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%% ____________________
%% INITIALIZATION
clc
clear
D=csvread('Data_volume_power.csv',2,0)
c1=D(:,1);
c2=D(:,2);
c3=D(:,3);
len=length(c1)
n1=zeros(12,1)
n2=zeros(12,1)


%% ____________________
%% CALCULATIONS
for x= 1:1:len
    p=c1(x,1);
    o4=67.1*log10(p)-1.3;
    n1(x,1)=o4;
    i3=77.7*log10(p)-7.3;
    n2(x,1)=i3;
end

 


%% ____________________
%% FORMATTED TEXT & FIGURE DISPLAYS
hold on
grid on
title('Power vs Decibels for two headphone sets')
xlabel('Power')
ylabel('Decibels')
plot(c1,c2,'r.-')
plot(c1,c3,'b.-')
plot(c1,n1,'rx--')
plot(c1,n2,'bx--')
legend({'OEP4 Actual values','IEP3 Actual values','OEP4 Predicted values','IEP3 Predicted values'},'Location','south')
hold off




%% ____________________
%% Analysis
%Q1: IEP3 fits its data better than OEP4.

%Q2: Based on the points from the models, the IEP3 headphones are more 
%sensitive.

%Q3: At 60dB the IEP3 headphones require less power therefore they will
%have a longer battery life. At 30dB, both sets of headphones require a
%almost the same amount of power, and the difference cannot be determined
%from the graph.



%% ____________________
%% ACADEMIC INTEGRITY STATEMENT
% I have not used source code obtained from any other unauthorized
% source, either modified or unmodified.  Neither have I provided
% access to my code to another. The project I am submitting
% is my own original work.