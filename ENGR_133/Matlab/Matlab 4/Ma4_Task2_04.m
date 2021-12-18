%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% ENGR 133 
% Program Description: 
%
% Assignment Information
%   Assignment:     Ma4 Task2
%   Team ID:        LC1-04
%  	Contributor:    Ayush Viswanathan, Jackson Bitterolf, Nolan Hays,
%  	Roshan Sundar
%   My contributor(s) helped me:	
%     [ ] understand the assignment expectations without
%         telling me how they will approach it.
%     [ ] understand different ways to think about a solution
%         without helping me plan my solution.
%     [ ] think through the meaning of a specific error or
%         bug present in my code without looking at my code.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%% ____________________
%% Function
pipe_calc([0.01:0.01:0.05], [0.03:0.02:0.09]);
pipe_calc([5 10 3], [0 1 2 3 4]);
pipe_calc([5 8 10], [2 4]);

function pipe_calc(D_pipe_list, D_rod_list)
    combo = [];
    for i=1:numel(D_pipe_list)
        for j=1:numel(D_rod_list)
            U = 2/(1000*pi*((D_pipe_list(i)/2)^2 - ((D_rod_list(j)/2)^2)));
            if U <= 0
                disp([-1 1 -1])
                return;
            elseif U < 300
                combo = [combo; D_pipe_list(i) D_rod_list(j)];
            end
        end
    end
    disp(combo)
end

%% ____________________
%% OUTPUTS

% pipe_calc([0.01:0.01:0.05], [0.03:0.02:0.09])
% -1     1    -1

% pipe_calc([5 10 3], [0 1 2 3 4])
% -1     1    -1

% pipe_calc([5 8 10], [2 4])
% 5     2
% 5     4
% 8     2
% 8     4
% 10     2
% 10     4

%% ____________________
%% ACADEMIC INTEGRITY STATEMENT
% I have not used source code obtained from any other unauthorized
% source, either modified or unmodified.  Neither have I provided
% access to my code to another. The project I am submitting
% is my own original work.