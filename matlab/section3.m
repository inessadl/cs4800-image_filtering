%% Reads the original image
f = imread('original.ppm');

%% Creates a copy of the image
imwrite(uint8(f), 'img_out2.ppm');
g = imread('img_out2.ppm');

%% Convert to grayscale and show it
g = rgb2gray(g);
imshow(g)
