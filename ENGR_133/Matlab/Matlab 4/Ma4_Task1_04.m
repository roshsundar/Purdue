Pool_Info(195,1);
%Pool_Info(80,0);
%Pool_Info([100 200],1);
%Pool_Info(-50,1);
%Pool_Info(45.5,1);
%Pool_Info(600,1);
%Pool_Info(100,2);
%Pool_Info(100,[0 1]);
function[]=Pool_Info(swimmers, diving)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% ENGR 133 
% Program Description 
%
% Function Call
%Pool_Info(2,0)
%
% Input Arguments
%swimmers, diving
%
%
% Assignment Information
%   Assignment:     Ma4_Task1
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
mat=csvread('Data_pool_info.csv',1,0);


%% ____________________
%% CALCULATIONS
if isscalar(swimmers)==0 || swimmers<=0 || floor(swimmers)~=swimmers
    fprintf('sorry your input is invalid, please make your amount of swimmers a scalar value or a nonzero whole number!\n')
    return
end
len=length(mat(:,1));
if swimmers>(mat(len,3)*mat(len,4))/25
    fprintf('sorry we cannot make a pool that big, decrease your amount of swimmers then try again!\n')
    return
end
if isscalar(diving)== 0 ||(diving~=1 && diving~=0)
    fprintf('sorry your diving input is invalid, please make your value 1 or 0 and scalar!\n')
    return
    
end
for i=1:1:9
    minutesCycle=480;
    surfaceArea=mat(i,3) * mat(i,4);
    maxSwimmers=surfaceArea/25;
     if diving==1
        if mat(i,2)<10
            continue
        end
     end
    if maxSwimmers>swimmers
        volume=mat(i,1);
        minFilt=volume/minutesCycle;
        fprintf('The volume of the pool is: %i\n',volume)
        fprintf('The maximum amount of swimmers is: %i\n',maxSwimmers)
        fprintf('The minimum filtration is: %i gal/min\n',minFilt)
        fprintf('The minimum number of inlets needed are: %i\n',round(minFilt/15))
        fprintf('\n')        
        break
    end
    
     
        
end
    



end


%% ____________________
%% Results
%Pool_Info(195,1)
%The volume of the pool is: 254000
%The maximum amount of swimmers is: 243
%The minimum filtration is: 5.291667e+02 gal/min
%The minimum number of inlets needed are: 35

%Pool_Info(80,0)
%The volume of the pool is: 120000
%The maximum amount of swimmers is: 108
%The minimum filtration is: 250 gal/min
%The minimum number of inlets needed are: 17

%Pool_Info([100 200],1)
%sorry your input is invalid, please make your amount of swimmers a scalar value or a nonzero whole number!

%Pool_Info(-50,1)
%sorry your input is invalid, please make your amount of swimmers a scalar value or a nonzero whole number!

%Pool_Info(45.5,1)
%sorry your input is invalid, please make your amount of swimmers a scalar value or a nonzero whole number!

%Pool_Info(600,1)
%sorry we cannot make a pool that big, decrease your amount of swimmers then try again!

%Pool_Info(100,2)
%sorry your diving input is invalid, please make your value 1 or 0 and scalar!

%Pool_Info(100,[0 1])
%sorry your diving input is invalid, please make your value 1 or 0 and scalar!




%% ____________________
%% ACADEMIC INTEGRITY STATEMENT
% I have not used source code obtained from any other unauthorized
% source, either modified or unmodified.  Neither have I provided
% access to my code to another. The project I am submitting
% is my own original work.