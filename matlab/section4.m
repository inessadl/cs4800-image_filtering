%% Open and show image
f = imread('img_out.ppm');
imshow(f)

f = imnoise(f, 'gaussian', 0, 0.1);
imshow(f)