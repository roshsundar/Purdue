%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% ENGR 133 
% Program Description: Rotate image 90 degrees counterclockwise
%
% Assignment Information
%   Assignment:     Ma4 Task4
%   Team ID:        LC1-04
%  	Contributor:    Roshan Sundar
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%% ____________________
%% Function
function out_img = Ma4_Task4_90_counterclockwise_rmsundar(in_img)
    %Create empty arrays for transformed x,y coords
    x1=zeros([size(in_img,1)*size(in_img,2) 1]);
    y1=zeros([size(in_img,1)*size(in_img,2) 1]);

    %Specify the degree
    deg=90;
    %Change the image size
    out_img=uint8(zeros([size(in_img,1) size(in_img,2) 3 ]));
    
    %Find the midpoint
    midx=ceil((size(out_img,1)+1)/2);
    midy=ceil((size(out_img,2)+1)/2);
    
    m=1;
    for i=1:size(in_img,1)
        for j=1:size(in_img,2)
            %convert from cartesian to polar
            [t,r]=cart2pol(i-midx,j-midy);
            %Convert from radians to degree and add the degree value
            t1=rad2deg(t)+deg;
            %Convert from degree to radians
            t=deg2rad(t1);
            %Convert to Cartesian Co-ordinates
            [x,y]=pol2cart(t,r);
            x1(m)=round(x+midx);
            y1(m)=round(y+midy);
            m=m+1;
        end
    end
    %check whether the values are within the image size.
    x1(find(x1 < 1))=1;
    y1(find(y1 < 1))=1;
    
    %Set each rotated output matrix pixel to the equivalent original
    %pixel
    n=1;
    for i=1:size(in_img,1)
        for j=1:size(in_img,2)
            out_img(x1(n),y1(n),:)=in_img(i,j,:);
            n=n+1;
        end
    end
end

%% ____________________
%% ACADEMIC INTEGRITY STATEMENT
% I have not used source code obtained from any other unauthorized
% source, either modified or unmodified.  Neither have I provided
% access to my code to another. The project I am submitting
% is my own original work.
% Algorithm inspired by https://www.imageeprocessing.com/2011/06/image-rotation.html