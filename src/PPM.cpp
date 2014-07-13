#include<stdio.h>
#include<stdlib.h>
#include "PPM.h"



PPMImage *readPPM(const char *filename)
{
	char buff[16];
	PPMImage *img;
	FILE *fp;
	int c, rgb_comp_color;

	//open PPM file for reading
	fopen_s(&fp, filename, "rb");
	if (!fp) {
		fprintf(stderr, "Unable to open file '%s'\n", filename);
		exit(1);
	}

	//read image format
	if (!fgets(buff, sizeof(buff), fp)) {
		perror(filename);
		exit(1);
	}

	//check the image format
	if (buff[0] != 'P' || buff[1] != '6' ) {
		fprintf(stderr, "Invalid image format (must be 'P6')\n");
		exit(1);
	}

	//alloc memory form image
	img = (PPMImage *)malloc(sizeof(PPMImage));
	if (!img) {
		fprintf(stderr, "Unable to allocate memory\n");
		exit(1);
	}

	//check for comments
	c = getc(fp);
	while (c == '#') {
		while (getc(fp) != '\n');
		c = getc(fp);
	}

	// read one char past where we wanted, back up
	ungetc(c, fp);
	//read image size information
	if (fscanf_s(fp, "%d %d", &img->x, &img->y) != 2) {
		fprintf(stderr, "Invalid image size (error loading '%s')\n", filename);
		exit(1);
	}

	//read rgb component
	if (fscanf_s(fp, "%d", &rgb_comp_color) != 1) {
		fprintf(stderr, "Invalid rgb component (error loading '%s')\n", filename);
		exit(1);
	}

	//check rgb component depth
	if (rgb_comp_color != RGB_COMPONENT_COLOR) {
		fprintf(stderr, "'%s' does not have 8-bits components\n", filename);
		exit(1);
	}

	while (fgetc(fp) != '\n');
	//memory allocation for pixel data
	img->data = (PPMPixel*)malloc(img->x * img->y * sizeof(PPMPixel));

	if (!img) {
		fprintf(stderr, "Unable to allocate memory\n");
		exit(1);
	}

	//read pixel data from file
	if (fread(img->data, 3 * img->x, img->y, fp) != img->y) {
		fprintf(stderr, "Error loading image '%s'\n", filename);
		exit(1);
	}

	fclose(fp);
	return img;
}

PPMGrayImage *readGrayPPM(const char *filename)
{
	char buff[16];
	PPMGrayImage *img;
	FILE *fp;
	int c, rgb_comp_color;

	//open PPM file for reading
	fopen_s(&fp, filename, "rb");
	if (!fp) {
		fprintf(stderr, "Unable to open file '%s'\n", filename);
		exit(1);
	}

	//read image format
	if (!fgets(buff, sizeof(buff), fp)) {
		perror(filename);
		exit(1);
	}

	//check the image format
	if (buff[0] != 'P' || buff[1] == '5') {
		fprintf(stderr, "Invalid image format (must be 'P5')\n");
		exit(1);
	}

	//alloc memory form image
	img = (PPMGrayImage *)malloc(sizeof(PPMGrayImage));
	if (!img) {
		fprintf(stderr, "Unable to allocate memory\n");
		exit(1);
	}

	//check for comments
	c = getc(fp);
	while (c == '#') {
		while (getc(fp) != '\n');
		c = getc(fp);
	}

	// read one char past where we wanted, back up
	ungetc(c, fp);
	//read image size information
	if (fscanf_s(fp, "%d %d", &img->x, &img->y) != 2) {
		fprintf(stderr, "Invalid image size (error loading '%s')\n", filename);
		exit(1);
	}

	//read rgb component
	if (fscanf_s(fp, "%d", &rgb_comp_color) != 1) {
		fprintf(stderr, "Invalid rgb component (error loading '%s')\n", filename);
		exit(1);
	}

	//check rgb component depth
	if (rgb_comp_color != RGB_COMPONENT_COLOR) {
		fprintf(stderr, "'%s' does not have 8-bits components\n", filename);
		exit(1);
	}

	while (fgetc(fp) != '\n');
	//memory allocation for pixel data
	img->data = (PPMGrayPixel*)malloc(img->x * img->y * sizeof(PPMGrayPixel));

	if (!img) {
		fprintf(stderr, "Unable to allocate memory\n");
		exit(1);
	}

	//read pixel data from file
	if (fread(img->data, img->x, img->y, fp) != img->y) {
		fprintf(stderr, "Error loading image '%s'\n", filename);
		exit(1);
	}

	fclose(fp);
	return img;
}

void writePPM(const char *filename, PPMImage *img)
{
	FILE *fp;
	//open file for output
	fopen_s(&fp, filename, "wb");
	if (!fp) {
		fprintf(stderr, "Unable to open file '%s'\n", filename);
		exit(1);
	}

	//write the header file
	//image format
	fprintf(fp, "P6\n");

	//comments
	fprintf(fp, "# Created by %s\n", CREATOR);

	//image size
	fprintf(fp, "%d %d\n", img->x, img->y);

	// rgb component depth
	fprintf(fp, "%d\n", RGB_COMPONENT_COLOR);

	// pixel data
	fwrite(img->data, 3 * img->x, img->y, fp);
	fclose(fp);
}

void writeGrayPPM(const char *filename, PPMGrayImage *img)
{
	FILE *fp;
	//open file for output
	fopen_s(&fp, filename, "wb");
	if (!fp) {
		fprintf(stderr, "Unable to open file '%s'\n", filename);
		exit(1);
	}

	//write the header file
	//image format
	fprintf(fp, "P5\n");

	//comments
	fprintf(fp, "# Created by %s\n", CREATOR);

	//image size
	fprintf(fp, "%d %d\n", img->x, img->y);

	// rgb component depth
	fprintf(fp, "%d\n", RGB_COMPONENT_COLOR);

	// pixel data
	fwrite(img->data, img->x, img->y, fp);
	fclose(fp);
}

PPMImage *CreateEmptyImage(PPMImage *img)
{
	PPMImage *target;

	//alloc memory form image
	target = (PPMImage *)malloc(sizeof(PPMImage));
	if (!target) {
		fprintf(stderr, "Unable to allocate memory\n");
		exit(1);
	}

	target->x = img->x;
	target->y = img->y;

	//memory allocation for pixel data
	target->data = (PPMPixel*)malloc(3 * img->x * img->y * sizeof(PPMPixel));
	
	return target;
}

PPMGrayImage *CreateEmptyGrayImage(PPMGrayImage *img)
{
	PPMGrayImage *target;

	//alloc memory for image
	target = (PPMGrayImage *)malloc(sizeof(PPMGrayImage));
	if (!target) {
		fprintf(stderr, "Unable to allocate memory\n");
		exit(1);
	}

	target->x = img->x;
	target->y = img->y;

	//memory allocation for pixel data
	target->data = (PPMGrayPixel*)malloc(3 * img->x * img->y * sizeof(PPMGrayPixel));

	return target;
}

PPMGrayImage *CreateEmptyGrayImageFromColorImage(PPMImage *img)
{
	PPMGrayImage *target;

	//alloc memory for image
	target = (PPMGrayImage *)malloc(sizeof(PPMGrayImage));
	if (!target) {
		fprintf(stderr, "Unable to allocate memory\n");
		exit(1);
	}

	target->x = img->x;
	target->y = img->y;

	//memory allocation for pixel data
	target->data = (PPMGrayPixel*)malloc(img->x * img->y * sizeof(PPMGrayPixel));

	return target;
}


// can't return void, should return an image
PPMImage * mask1(PPMImage *img){

	int i;
	int average;

	/* USING GRAYSCALE JUST TO TEST THE PARAMETERS */

	/* Makes a copy of the image to apply the filter and don't lose data */

	if (img){

		/* Go through each pixel of the image */
		for (i = 0; i < img->x*img->y; i++) {

			/* Calculates average of the values in each channel (rgb) and
			set the pixels with the new value */
			average = (img->data[i].red + img->data[i].green + img->data[i].blue) / 3;

			img->data[i].red = average;
			img->data[i].green = average;
			img->data[i].blue = average;
		}
		return img;
	}
}

PPMImage * mask2(PPMImage *img) {

	return img;
}

/* DELETE THIS FUNCTION*/ /* Function to convert a RGB image in a Grayscale - uses the average method */
void changeToGrayScale(PPMImage *img) {
	int i;
	int average;

	if (img) {

		/* Go through each pixel of the image */
		for (i = 0; i < img->x*img->y; i++) {

			/* Calculates average of the values in each channel (rgb) and
			set the pixels with the new value */
			average = (img->data[i].red + img->data[i].green + img->data[i].blue) / 3;

			img->data[i].red = average;
			img->data[i].green = average;
			img->data[i].blue = average;

		}
	}
}


PPMGrayImage * ConvertToGrayFromColorImage(PPMImage *img) {

	PPMGrayImage *img2;
	img2 = CreateEmptyGrayImageFromColorImage(img);


	for (int i=0; i < img2->x*img2->y; i++) {

		printf("%d\n", &i);
		/*
		if (i % 2 == 0) {
			img2->data[i].gray = 0;
		}
		else {
			img2->data[i].gray = 255;
		}
		*/
		if (i > 255 && i < 1350) {
			img2->data[i].gray = 255;
		}


	}


	return img2;
}