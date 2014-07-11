%% Open and show original image
f = imread('originalColored.ppm');
imshow(f)

%% Gets information about the file
whos f

%% Convert to grayscale and show it
g = rgb2gray(f);
imshow(g)
% image(f)
% colormap(gray(256));
% truesize;

%% Show all images
imshow(f), figure, imshow(g)

