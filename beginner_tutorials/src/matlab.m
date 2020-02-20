
% import image
img = imread('test.jpg');
 
%get sizes
[r,c,d] = size(img);
imshow(img)
%set up reference img
mask = zeros(r,c,d);
imshow(mask)
%search through the rows
for i = 1 : r
%     search through the coloums
    for j = 1 : c
%         if found the colors apple the mask
%         anything left out didn't match the color
        if img(i,j,3) > 200
            if img(i, j, 2) < 150
                if img(i,j,1) < 100
                    mask(i,j,1) = img(i,j,1);
                    mask(i,j,2) = img(i,j,2);
                    mask(i,j,3) = img(i,j,3);
                end
            end
        end
    end
end
 
line1 = round(r * 0.75);
line2 = round(r * 0.50);
line3 = round(r * 0.25);
 
for i = 1 : c
%     paint line
    mask(200,i,2) = 255;
    mask(line1,i,2) = 255;
    mask(line2,i,2) = 255;
    mask(line3,i,2) = 255;
end
j = 0
for i = 1 : c
    if(mask(201,i,1) > 1)
        j = j +1;
        mid(j) = i;
    end
end
 
midPoint = round(mean(mid))
 
for i = 1 : r
    mask(i,midPoint,1) = 255;
end
 
% show at the end
% imshow(mask)
% subplot(1,2,1), imshow(img)
% subplot(1,2,2), imshow(mask)
 
% tabl3 = array2table(mask)
testi = mask(:,:,2);
% writematrix(testi, 'testingfile_out.xlsx')
 
imshow(mask);
 
%% testing for tape (found yellow testing one
file = 1;
img = imread('3.jpg');
 
%get sizes
[r,c,d] = size(img)
imshow(img)
%set up reference img
mask = zeros(r,c,3);
 
colorvalues = [230,0,230];
 
%search through the rows
for i = 1 : r
%     search through the coloums
    for j = 1 : c
%         if found the colors apple the mask
%         anything left out didn't match the color
        if img(i,j,3) < colorvalues(3)
            if img(i, j, 2) > colorvalues(2)
                if img(i,j,1) < colorvalues(1)
                    mask(i,j,1) = img(i,j,1);
                    mask(i,j,2) = img(i,j,2);
                    mask(i,j,3) = img(i,j,3);
                end
            end
        end
    end
end
% show at the end
% imshow(mask)
subplot(1,2,1), imshow(img)
subplot(1,2,2), imshow(mask)
 
%% testing for tape finding blue test one
file = 1;
img = imread('1.jpg');
 
%get sizes
[r,c,d] = size(img)
imshow(img)
%set up reference img
mask = zeros(r,c,3);
 
colorvalues = [40,100,0];
 
%search through the rows
for i = 1 : r
%     search through the coloums
    for j = 1 : c
%         if found the colors apple the mask
%         anything left out didn't match the color
        if img(i,j,3) > colorvalues(3)
            if img(i, j, 2) < colorvalues(2)
                if img(i,j,1) < colorvalues(1)
                    mask(i,j,1) = img(i,j,1);
                    mask(i,j,2) = img(i,j,2);
                    mask(i,j,3) = img(i,j,3);
                end
            end
        end
    end
end
% show at the end
% imshow(mask)
subplot(1,2,1), imshow(img)
subplot(1,2,2), imshow(mask)
 

%% testing
 
masky = zeros(r,c,3);
 
for i = 1 : r
    for j = 1 : c
        masky(i,j,1) = 255;
        
        imshow(masky)
    end
end

