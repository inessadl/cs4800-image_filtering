%% Reads original image
f = imread('original.ppm');

%% Writes image
imwrite(uint8(f),'img_out.ppm');

%% Reads new image
g = imread('img_out.ppm');

%% Displays images
imshow(f), figure, imshow(g);

