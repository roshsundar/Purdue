%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% ENGR 133 
% Program Description 
%replace this text with your program description as a comment
%
% Assignment Information
%   Assignment:     Ma4_Task 3
%   Author:         Ayush Viswanathan, viswan11@purdue.edu
%   Team ID:        LC1-04
%  	Contributor:    Jackson Bitterolf, jbittero@purdue.edu
%                   Nolan Hays, haysn@purdue.edu
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
%% INITIALIZATIONS
M = input('Number of Rows: ');
N = input('Number of Columns: ');
matrix = zeros(M,N);
%% ____________________
%% CALCULATIONS
for i = 1:M
    for j = 1:N
        x = i * j;
        if mod(x,2) ~= 0
            matrix(i,j) = 0;
        end
        if mod(x,2) == 0
            matrix(i,j) = x;
        end
        if i == j
            matrix(i,j) = -1;
        end
    end
end

%% ____________________
%% OUTPUTS
disp(matrix);

%Case 1: M = 1, N = 5
%   Number of Rows: 1
%   Number of Columns: 5
%       -1     2     0     4     0

%Case 2: M = 4, N = 3
    %Number of Rows: 4
    %Number of Columns: 3
    %    -1     2     0
    %     2    -1     6
    %     0     6    -1
    %     4     8    12


%% ____________________
%% ACADEMIC INTEGRITY STATEMENT
% I have not used source code obtained from any other unauthorized
% source, either modified or unmodified.  Neither have I provided
% access to my code to another. The project I am submitting
% is my own original work.