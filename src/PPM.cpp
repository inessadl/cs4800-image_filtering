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


/* IT'S RETURNING A PPMIMAGE - SEE A SOLUTION TO GRAY IMAGE*/

/* Function that applies the (3x3) mask 1:
	| 1 | 2 | 1 |
	| 2 | 4 | 2 |
	| 1 | 2 | 1 | */
PPMImage * mask1(PPMImage *img){

	int gred, ggreen, gblue;
	int i, j;
	int x = img->x;
	int y = img->y;

	/* Makes a copy of the image to apply the filter and don't lose data */
	PPMImage *img2;
	img2 = CreateEmptyImage(img);

	

	if (img){

		/* Go through each pixel of the image */
		for (i = 0; i < img->x*img->y; i++) {

			/* #1 TOP-LEFT corner 
			*
			* Multiplies the pixel by 4, the pixels with distance 1 from it are mutiplied by 2,
			* the pixels with distance 2 are supposed to be multiplied by 1, but any operation is
			* done. Once that is in the border, not all pixels were considered. The result of the 
			* operation is divided by 8. 
			*/
			if (i == 0) {

				j = i;

				/* RED channel of the pixel */
				gred = (
					(img->data[j].red * 4) +

					(img->data[j + 1].red * 2) +
					(img->data[j + x].red * 2) +

					img->data[j + (x + 1)].red
					) / 8;

				/* GREEN channel of the pixel */
				ggreen = (
					(img->data[j].green * 4) +

					(img->data[j + 1].green * 2) +
					(img->data[j + x].green * 2) +

					img->data[j + (x + 1)].green
					) / 8;

				/* BLUE channel of the pixel */
				gblue = (
					(img->data[j].blue * 4) +

					(img->data[j + 1].blue * 2) +
					(img->data[j + x].blue * 2) +

					img->data[j + (x + 1)].blue
					) / 8;


				/* If a result is larger than the range, adjusts to the maximum value (255) */
				if (gred > 255)		{ gred = 255; }
				if (ggreen > 255)	{ ggreen = 255; }
				if (gblue > 255)	{ gblue = 255; }

				/* If a result is smaller than the range, adjusts to the minimum value (0) */
				if (gred < 0)		{ gred = 0; }
				if (ggreen < 0)		{ ggreen = 0; }
				if (gblue < 0)		{ gblue = 0; }

				/* After adjusted, the value is set on each channel */
				img2->data[j].red = gred;
				img2->data[j].green = ggreen;
				img2->data[j].blue = gblue;
			}


			/* #2 TOP
			* 
			* Multiplies the pixel by 4, the pixels with distance 1 from it are mutiplied by 2,
			* the pixels with distance 2 are supposed to be multiplied by 1, but any operation is
			* done. Once that is in the border, not all pixels were considered. The result of the
			* operation is divided by 12. 
			*/
			else if (i>0 && i < (x - 1)) {

				j = i;

				/* RED channel of the pixel */
				gred = (
					(img->data[j].red * 4) +

					(img->data[j - 1].red * 2) +
					(img->data[j + 1].red * 2) +
					(img->data[j + x].red * 2) +

					img->data[j + x - 1].red +
					img->data[j + x + 1].red
					) / 12;

				/* GREEN channel of the pixel */
				ggreen = (
					(img->data[j].green * 4) +

					(img->data[j - 1].green * 2) +
					(img->data[j + 1].green * 2) +
					(img->data[j + x].green * 2) +

					img->data[j + x - 1].green +
					img->data[j + x + 1].green
					) / 12;

				/* BLUE channel of the pixel */
				gblue = (
					(img->data[j].blue * 4) +

					(img->data[j - 1].blue * 2) +
					(img->data[j + 1].blue * 2) +
					(img->data[j + x].blue * 2) +

					img->data[j + x - 1].blue +
					img->data[j + x + 1].blue
					) / 12;


				/* If a result is larger than the range, adjusts to the maximum value (255) */
				if (gred > 255)		{ gred = 255; }
				if (ggreen > 255)	{ ggreen = 255; }
				if (gblue > 255)	{ gblue = 255; }

				/* If a result is smaller than the range, adjusts to the minimum value (0) */
				if (gred < 0)		{ gred = 0; }
				if (ggreen < 0)		{ ggreen = 0; }
				if (gblue < 0)		{ gblue = 0; }

				/* After adjusted, the value is set on each channel */
				img2->data[j].red = gred;
				img2->data[j].green = ggreen;
				img2->data[j].blue = gblue;
			}

			/* # 3 TOP-RIGHT corner
			*
			* Multiplies the pixel by 4, the pixels with distance 1 from it are mutiplied by 2,
			* the pixels with distance 2 are supposed to be multiplied by 1, but any operation is
			* done. Once that is in the border, not all pixels were considered. The result of the
			* operation is divided by 8. 
			*/
			else if (i == (x - 1)) {
				
				j = i;

				/* RED channel of the pixel */
				gred = (
					(img->data[j].red * 4) +

					(img->data[j - 1].red * 2) +
					(img->data[j + x].red * 2) +

					img->data[j + (x - 1)].red
					) / 8;

				/* GREEN channel of the pixel */
				ggreen = (
					(img->data[j].green * 4) +

					(img->data[j - 1].green * 2) +
					(img->data[j + x].green * 2) +

					img->data[j + (x - 1)].green
					) / 8;

				/* BLUE channel of the pixel */
				gblue = (
					(img->data[j].blue * 4) +

					(img->data[j - 1].blue * 2) +
					(img->data[j + x].blue * 2) +

					img->data[j + (x - 1)].blue
					) / 8;


				/* If a result is larger than the range, adjusts to the maximum value (255) */
				if (gred > 255)		{ gred = 255; }
				if (ggreen > 255)	{ ggreen = 255; }
				if (gblue > 255)	{ gblue = 255; }

				/* If a result is smaller than the range, adjusts to the minimum value (0) */
				if (gred < 0)		{ gred = 0; }
				if (ggreen < 0)		{ ggreen = 0; }
				if (gblue < 0)		{ gblue = 0; }

				/* After adjusted, the value is set on each channel */
				img2->data[j].red = gred;
				img2->data[j].green = ggreen;
				img2->data[j].blue = gblue;

			}
			/* #4 BOTTOM-RIGHT corner 
			*
			* Multiplies the pixel by 4, the pixels with distance 1 from it are mutiplied by 2,
			* the pixels with distance 2 are supposed to be multiplied by 1, but any operation is
			* done. Once that is in the border, not all pixels were considered. The result of the
			* operation is divided by 8.
			*/
			else if (i == (x * y) - 1) {

				j = i;


				/* RED channel of the pixel */
				gred = (
					(img->data[j].red * 4) +

					(img->data[j - 1].red * 2) +
					(img->data[j - x].red * 2) +

					img->data[j - x - 1].red
					) / 8;

				/* GREEN channel of the pixel */
				ggreen = (
					(img->data[j].green * 4) +

					(img->data[j - 1].green * 2) +
					(img->data[j - x].green * 2) +

					img->data[j - x - 1].green
					) / 8;

				/* BLUE channel of the pixel */
				gblue = (
					(img->data[j].blue * 4) +

					(img->data[j - 1].blue * 2) +
					(img->data[j - x].blue * 2) +

					img->data[j - x - 1].blue
					) / 8;


				/* If a result is larger than the range, adjusts to the maximum value (255) */
				if (gred > 255)		{ gred = 255; }
				if (ggreen > 255)	{ ggreen = 255; }
				if (gblue > 255)	{ gblue = 255; }

				/* If a result is smaller than the range, adjusts to the minimum value (0) */
				if (gred < 0)		{ gred = 0; }
				if (ggreen < 0)		{ ggreen = 0; }
				if (gblue < 0)		{ gblue = 0; }

				/* After adjusted, the value is set on each channel */
				img2->data[j].red = gred;
				img2->data[j].green = ggreen;
				img2->data[j].blue = gblue;
			}


			/* #5 BOTTOM-LEFT corner
			*
			* Multiplies the pixel by 4, the pixels with distance 1 from it are mutiplied by 2,
			* the pixels with distance 2 are supposed to be multiplied by 1, but any operation is
			* done. Once that is in the border, not all pixels were considered. The result of the
			* operation is divided by 8.
			*/
			else if (i == (x*y) - x) {
				
				j = i;

				/* RED channel of the pixel */
				gred = (
					(img->data[j].red * 4) +
					(img->data[j + 1].red * 2) +
					(img->data[j - x].red * 2) +

					img->data[j - (x + 1)].red
					) / 8;

				/* GREEN channel of the pixel */
				ggreen = (
					(img->data[j].green * 4) +
					(img->data[j + 1].green * 2) +
					(img->data[j - x].green * 2) +

					img->data[j - (x + 1)].green
					) / 8;

				/* BLUE channel of the pixel */
				gblue = (
					(img->data[j].blue * 4) +
					(img->data[j + 1].blue * 2) +
					(img->data[j - x].blue * 2) +

					img->data[j - (x + 1)].blue
					) / 8;


				/* If a result is larger than the range, adjusts to the maximum value (255) */
				if (gred > 255)		{ gred = 255; }
				if (ggreen > 255)	{ ggreen = 255; }
				if (gblue > 255)	{ gblue = 255; }

				/* If a result is smaller than the range, adjusts to the minimum value (0) */
				if (gred < 0)		{ gred = 0; }
				if (ggreen < 0)		{ ggreen = 0; }
				if (gblue < 0)		{ gblue = 0; }

				/* After adjusted, the value is set on each channel */
				img2->data[j].red = gred;
				img2->data[j].green = ggreen;
				img2->data[j].blue = gblue;
			}


			/* #6 BOTTOM
			* 
			* Multiplies the pixel by 4, the pixels with distance 1 from it are mutiplied by 2,
			* the pixels with distance 2 are supposed to be multiplied by 1, but any operation is
			* done. Once that is in the border, not all pixels were considered. The result of the
			* operation is divided by 12. 
			*/
			else if (i >= (x*y) - x && i < (x * y) - 1) {
				
				j = i;
				
				/* RED channel of the pixel */
				gred = (
					(img->data[j].red * 4) +

					(img->data[j - 1].red * 2) +
					(img->data[j + 1].red * 2) +
					(img->data[j - x].red * 2) +

					img->data[j - x - 1].red +
					img->data[j - x + 1].red
					) / 12;

				/* GREEN channel of the pixel */
				ggreen = (
					(img->data[j].green * 4) +

					(img->data[j - 1].green * 2) +
					(img->data[j + 1].green * 2) +
					(img->data[j - x].green * 2) +

					img->data[j - x - 1].green +
					img->data[j - x + 1].green
					) / 12;

				/* BLUE channel of the pixel */
				gblue = (
					(img->data[j].blue * 4) +

					(img->data[j - 1].blue * 2) +
					(img->data[j + 1].blue * 2) +
					(img->data[j - x].blue * 2) +

					img->data[j - x - 1].blue +
					img->data[j - x + 1].blue
					) / 12;


				/* If a result is larger than the range, adjusts to the maximum value (255) */
				if (gred > 255)		{ gred = 255; }
				if (ggreen > 255)	{ ggreen = 255; }
				if (gblue > 255)	{ gblue = 255; }

				/* If a result is smaller than the range, adjusts to the minimum value (0) */
				if (gred < 0)		{ gred = 0; }
				if (ggreen < 0)		{ ggreen = 0; }
				if (gblue < 0)		{ gblue = 0; }

				/* After adjusted, the value is set on each channel */
				img2->data[j].red = gred;
				img2->data[j].green = ggreen;
				img2->data[j].blue = gblue;

			}


			/* #7 LEFT */
			else if (i%x == 0) {
				j = i;

				/* RED channel of the pixel */
				gred = (
					(img->data[j].red * 4) +

					(img->data[j + 1].red * 2) +
					(img->data[j + x].red * 2) +
					(img->data[j - x].red * 2) +

					img->data[j - x + 1].red +
					img->data[j - x + 1].red
					) / 12;

				/* GREEN channel of the pixel */
				ggreen = (
					(img->data[j].green * 4) +

					(img->data[j + 1].green * 2) +
					(img->data[j + x].green * 2) +
					(img->data[j - x].green * 2) +

					img->data[j - x + 1].green +
					img->data[j - x + 1].green
					) / 12;

				/* BLUE channel of the pixel */
				gblue = (
					(img->data[j].blue * 4) +

					(img->data[j + 1].blue * 2) +
					(img->data[j + x].blue * 2) +
					(img->data[j - x].blue * 2) +

					img->data[j - x + 1].blue +
					img->data[j - x + 1].blue
					) / 12;


				/* If a result is larger than the range, adjusts to the maximum value (255) */
				if (gred > 255)		{ gred = 255; }
				if (ggreen > 255)	{ ggreen = 255; }
				if (gblue > 255)	{ gblue = 255; }

				/* If a result is smaller than the range, adjusts to the minimum value (0) */
				if (gred < 0)		{ gred = 0; }
				if (ggreen < 0)		{ ggreen = 0; }
				if (gblue < 0)		{ gblue = 0; }

				/* After adjusted, the value is set on each channel */
				img2->data[j].red = gred;
				img2->data[j].green = ggreen;
				img2->data[j].blue = gblue;
			}


			/* #8 RIGHT */

			/* Multiplies the pixel by 4, the pixels with distance 1 from it are mutiplied by 2,
			the pixels with distance 2 are supposed to be multiplied by 1, but any operation is
			done. Once that is in the border, not all pixels were considered. The result of the
			operation is divided by 12. */
			else if ((i + 1) % x == 0) {
				
				

				j = i;

				/* RED channel of the pixel */
				gred = (
					(img->data[j].red * 4) +

					(img->data[j - 1].red * 2) +
					(img->data[j - x].red * 2) +
					(img->data[j + x].red * 2) +

					img->data[j - x - 1].red
					+ img->data[j + (x - 1)].red
					) / 12;

				/* GREEN channel of the pixel */
				ggreen = (
					(img->data[j].green * 4) +

					(img->data[j - 1].green * 2) +
					(img->data[j - x].green * 2) +
					(img->data[j + x].green * 2) +

					img->data[j - x - 1].green +
					img->data[j + (x - 1)].green
					) / 12;

				/* BLUE channel of the pixel */
				gblue = (
					(img->data[j].blue * 4) +

					(img->data[j - 1].blue * 2) +
					(img->data[j - x].blue * 2) +
					(img->data[j + x].blue * 2) +

					img->data[j - x - 1].blue +
					img->data[j + (x - 1)].blue
					) / 12;


				/* If a result is larger than the range, adjusts to the maximum value (255) */
				if (gred > 255)		{ gred = 255; }
				if (ggreen > 255)	{ ggreen = 255; }
				if (gblue > 255)	{ gblue = 255; }

				/* If a result is smaller than the range, adjusts to the minimum value (0) */
				if (gred < 0)		{ gred = 0; }
				if (ggreen < 0)		{ ggreen = 0; }
				if (gblue < 0)		{ gblue = 0; }

				/* After adjusted, the value is set on each channel */
				img2->data[j].red = gred;
				img2->data[j].green = ggreen;
				img2->data[j].blue = gblue;

			}


			/* #9 MIDDLE
			*
			* Multiply the pixel by 4, the pixels with distance 1 from it are mutiplied by 2,
			* the pixels with distance 2 are supposed to be multiplied by 1, but any operation is
			* done.The result is divided by 15. 
			*/
			else {

				j = i;

				/* RED channel of the pixel */
				gred = (
					(img->data[j].red * 4) +

					(img->data[j - x].red * 2) +
					(img->data[j + x].red * 2) +
					(img->data[j + 1].red * 2) +
					(img->data[j - 1].red * 2) +

					img->data[j + (x - 1)].red +
					img->data[j + (x + 1)].red +
					img->data[j - x - 1].red +
					img->data[j - x + 1].red

					) / 15;

				/* GREEN channel of the pixel */
				ggreen = (
					(img->data[j].green * 4) +

					(img->data[j - x].green * 2) +
					(img->data[j + x].green * 2) +
					(img->data[j + 1].green * 2) +
					(img->data[j - 1].green * 2) +

					img->data[j + (x - 1)].green +
					img->data[j + (x + 1)].green +
					img->data[j - x - 1].green +
					img->data[j - x + 1].green

					) / 15;

				/* BLUE channel of the pixel */
				gblue = (
					(img->data[j].blue * 4) +

					(img->data[j - x].blue * 2) +
					(img->data[j + x].blue * 2) +
					(img->data[j + 1].blue * 2) +
					(img->data[j - 1].blue * 2) +

					img->data[j + (x - 1)].blue +
					img->data[j + (x + 1)].blue +
					img->data[j - x - 1].blue +
					img->data[j - x + 1].blue

					) / 15;


				/* If a result is larger than the range, adjusts to the maximum value (255) */
				if (gred > 255)		{ gred = 255; }
				if (ggreen > 255)	{ ggreen = 255; }
				if (gblue > 255)	{ gblue = 255; }

				/* If a result is smaller than the range, adjusts to the minimum value (0) */
				if (gred < 0)		{ gred = 0; }
				if (ggreen < 0)		{ ggreen = 0; }
				if (gblue < 0)		{ gblue = 0; }

				/* After adjusted, the value is set on each channel */
				img2->data[j].red = gred;
				img2->data[j].green = ggreen;
				img2->data[j].blue = gblue;
			}
		}

		return img2;
	}
}

/* Function that applies the (3x3) mask 1:
	| -1 | -1 | -1 |
	| -1 |  8 | -1 |
	| -1 | -1 | -1 | */
PPMImage * mask2(PPMImage *img) {

	int gred, ggreen, gblue;
	int i, j;
	int x = img->x;
	int y = img->y;

	/* Makes a copy of the image to apply the filter and don't lose data */
	PPMImage *img2;
	img2 = CreateEmptyImage(img);

	if (img){

		/* Go through each pixel of the image */
		for (i = 0; i < img->x*img->y; i++){

			// # 1 TOP-LEFT corner
			if (i == 0) {

				
				j = i;

				/* The pixel is multiplied by 3 and the result is subtracted by its neighbors */

				/* RED channel of the pixel */
				gred = img->data[j].red * 3 - (img->data[j + 1].red +
					img->data[j + x].red +
					img->data[j + (x + 1)].red
					);

				/* GREEN channel of the pixel */
				ggreen = img->data[j].green * 3 - (img->data[j + 1].green +
					img->data[j + x].green +
					img->data[j + (x + 1)].green
					);
				/* BLUE channel of the pixel */
				gblue = img->data[j].blue * 3 - (img->data[j + 1].blue +
					img->data[j + x].blue +
					img->data[j + (x + 1)].blue
					);


				/* If a result is larger than the range, adjusts to the maximum value (255) */
				if (gred > 255)		{ gred = 255; }
				if (ggreen > 255)	{ ggreen = 255; }
				if (gblue > 255)	{ gblue = 255; }

				/* If a result is smaller than the range, adjusts to the minimum value (0) */
				if (gred < 0)		{ gred = 0; }
				if (ggreen < 0)		{ ggreen = 0; }
				if (gblue < 0)		{ gblue = 0; }

				/* After adjusted, the value is set on each channel */
				img2->data[j].red = gred;
				img2->data[j].green = ggreen;
				img2->data[j].blue = gblue;

			}



			// # 2 TOP
			else if (i > 0 && i < (x - 1)) {
				
				j = i;

				/* The pixel is multiplied by 5 and the result is subtracted by its neighbors */

				/* RED channel of the pixel */
				gred = img->data[j].red * 5 - (img->data[j - 1].red +
					img->data[j + 1].red +
					img->data[j + x].red +
					img->data[j + x - 1].red +
					img->data[j + x + 1].red
					);

				/* GREEN channel of the pixel */
				ggreen = img->data[j].green * 5 - (img->data[j - 1].green +
					img->data[j + 1].green +
					img->data[j + x].green +
					img->data[j + x - 1].green +
					img->data[j + x + 1].green
					);

				/* BLUE channel of the pixel */
				gblue = img->data[j].blue * 5 - (img->data[j - 1].blue +
					img->data[j + 1].blue +
					img->data[j + x].blue +
					img->data[j + x - 1].blue +
					img->data[j + x + 1].blue
					);

				/* If a result is larger than the range, adjusts to the maximum value (255) */
				if (gred > 255)		{ gred = 255; }
				if (ggreen > 255)	{ ggreen = 255; }
				if (gblue > 255)	{ gblue = 255; }

				/* If a result is smaller than the range, adjusts to the minimum value (0) */
				if (gred < 0)		{ gred = 0; }
				if (ggreen < 0)		{ ggreen = 0; }
				if (gblue < 0)		{ gblue = 0; }

				/* After adjusted, the value is set on each channel */
				img2->data[j].red = gred;
				img2->data[j].green = ggreen;
				img2->data[j].blue = gblue;
			}



			// # 3 TOP-RIGHT corner
			else if (i == (x - 1)) {
				
				j = i;

				/* The pixel is multiplied by 3 and the result is subtracted by its neighbors */

				/* RED channel of the pixel */
				gred = img->data[j].red * 3 - (img->data[j - 1].red +
					img->data[j + x].red +
					img->data[j + (x - 1)].red
					);

				/* GREEN channel of the pixel */
				ggreen = img->data[j].green * 3 - (img->data[j - 1].green +
					img->data[j + x].green +
					img->data[j + (x - 1)].green
					);

				/* BLUE channel of the pixel */
				gblue = img->data[j].blue * 3 - (img->data[j - 1].blue +
					img->data[j + x].blue +
					img->data[j + (x - 1)].blue
					);


				/* If a result is larger than the range, adjusts to the maximum value (255) */
				if (gred > 255)		{ gred = 255; }
				if (ggreen > 255)	{ ggreen = 255; }
				if (gblue > 255)	{ gblue = 255; }

				/* If a result is smaller than the range, adjusts to the minimum value (0) */
				if (gred < 0)		{ gred = 0; }
				if (ggreen < 0)		{ ggreen = 0; }
				if (gblue < 0)		{ gblue = 0; }

				/* After adjusted, the value is set on each channel */
				img2->data[j].red = gred;
				img2->data[j].green = ggreen;
				img2->data[j].blue = gblue;
			}



			// # 4 BOTTOM-RIGHT corner
			else if (i == (x * y) - 1) {
				
				j = i;

				/* The pixel is multiplied by 3 and the result is subtracted by its neighbors */

				/* RED channel of the pixel */
				gred = img->data[j].red * 3 - (img->data[j - 1].red +
					img->data[j - x].red +
					img->data[j - x - 1].red
					);

				/* GREEN channel of the pixel */
				ggreen = img->data[j].green * 3 - (img->data[j - 1].green +
					img->data[j - x].green +
					img->data[j - x - 1].green
					);

				/* BLUE channel of the pixel */
				gblue = img->data[j].blue * 3 - (img->data[j - 1].blue +
					img->data[j - x].blue +
					img->data[j - x - 1].blue
					);


				/* If a result is larger than the range, adjusts to the maximum value (255) */
				if (gred > 255)		{ gred = 255; }
				if (ggreen > 255)	{ ggreen = 255; }
				if (gblue > 255)	{ gblue = 255; }

				/* If a result is smaller than the range, adjusts to the minimum value (0) */
				if (gred < 0)		{ gred = 0; }
				if (ggreen < 0)		{ ggreen = 0; }
				if (gblue < 0)		{ gblue = 0; }

				/* After adjusted, the value is set on each channel */
				img2->data[j].red = gred;
				img2->data[j].green = ggreen;
				img2->data[j].blue = gblue;

			}



			// # 5 BOTTOM-LEFT corner
			else if (i == (x*y) - x) {
				

				j = i;

				/* The pixel is multiplied by 3 and the result is subtracted by its neighbors */

				/* RED channel of the pixel */
				gred = img->data[j].red * 3 - (img->data[j + 1].red +
					img->data[j - x].red +
					img->data[j - (x + 1)].red
					);

				/* GREEN channel of the pixel */
				ggreen = img->data[j].green * 3 - (img->data[j + 1].green +
					img->data[j - x].green +
					img->data[j - (x + 1)].green
					);

				/* BLUE channel of the pixel */
				gblue = img->data[j].blue * 3 - (img->data[j + 1].blue +
					img->data[j - x].blue +
					img->data[j - (x + 1)].blue
					);


				/* If a result is larger than the range, adjusts to the maximum value (255) */
				if (gred > 255)		{ gred = 255; }
				if (ggreen > 255)	{ ggreen = 255; }
				if (gblue > 255)	{ gblue = 255; }

				/* If a result is smaller than the range, adjusts to the minimum value (0) */
				if (gred < 0)		{ gred = 0; }
				if (ggreen < 0)		{ ggreen = 0; }
				if (gblue < 0)		{ gblue = 0; }

				/* After adjusted, the value is set on each channel */
				img2->data[j].red = gred;
				img2->data[j].green = ggreen;
				img2->data[j].blue = gblue;


			}



			// # 6 BOTTOM
			else if (i >= (x*y) - x && i < (x * y) - 1) {
				
				j = i;

				/* The pixel is multiplied by 5 and the result is subtracted by its neighbors */

				/* RED channel of the pixel */
				gred = img->data[j].red * 5 - (img->data[j - 1].red +
					img->data[j + 1].red +
					img->data[j - x].red +
					img->data[j - x - 1].red +
					img->data[j - x + 1].red
					);

				/* GREEN channel of the pixel */
				ggreen = img->data[j].green * 5 - (img->data[j - 1].green +
					img->data[j + 1].green +
					img->data[j - x].green +
					img->data[j - x - 1].green +
					img->data[j - x + 1].green
					);

				/* BLUE channel of the pixel */
				gblue = img->data[j].blue * 5 - (img->data[j - 1].blue +
					img->data[j + 1].blue +
					img->data[j - x].blue +
					img->data[j - x - 1].blue +
					img->data[j - x + 1].blue
					);

				/* If a result is larger than the range, adjusts to the maximum value (255) */
				if (gred > 255)		{ gred = 255; }
				if (ggreen > 255)	{ ggreen = 255; }
				if (gblue > 255)	{ gblue = 255; }

				/* If a result is smaller than the range, adjusts to the minimum value (0) */
				if (gred < 0)		{ gred = 0; }
				if (ggreen < 0)		{ ggreen = 0; }
				if (gblue < 0)		{ gblue = 0; }

				/* After adjusted, the value is set on each channel */
				img2->data[j].red = gred;
				img2->data[j].green = ggreen;
				img2->data[j].blue = gblue;


			}



			// # 7 LEFT 
			else if (i%x == 0) {
				

				j = i;

				/* The pixel is multiplied by 5 and the result is subtracted by its neighbors */

				/* RED channel of the pixel */
				gred = img->data[j].red * 5 - (img->data[j + 1].red +
					img->data[j + x].red +
					img->data[j - x + 1].red +
					img->data[j - x].red +
					img->data[j - x + 1].red
					);

				/* GREEN channel of the pixel */
				ggreen = img->data[j].green * 5 - (img->data[j + 1].green +
					img->data[j + x].green +
					img->data[j - x + 1].green +
					img->data[j - x].green +
					img->data[j - x + 1].green
					);

				/* BLUE channel of the pixel */
				gblue = img->data[j].blue * 5 - (img->data[j + 1].blue +
					img->data[j + x].blue +
					img->data[j - x + 1].blue +
					img->data[j - x].blue +
					img->data[j - x + 1].blue
					);

				/* If a result is larger than the range, adjusts to the maximum value (255) */
				if (gred > 255)		{ gred = 255; }
				if (ggreen > 255)	{ ggreen = 255; }
				if (gblue > 255)	{ gblue = 255; }

				/* If a result is smaller than the range, adjusts to the minimum value (0) */
				if (gred < 0)		{ gred = 0; }
				if (ggreen < 0)		{ ggreen = 0; }
				if (gblue < 0)		{ gblue = 0; }

				/* After adjusted, the value is set on each channel */
				img2->data[j].red = gred;
				img2->data[j].green = ggreen;
				img2->data[j].blue = gblue;


			}



			// # 8 RIGHT
			else if ((i + 1) % x == 0) {
				
				j = i;


				/* The pixel is multiplied by 5 and the result is subtracted by its neighbors */

				/* RED channel of the pixel */
				gred = img->data[j].red * 5 - (img->data[j - 1].red +
					img->data[j - x].red +
					img->data[j - x - 1].red +
					img->data[j + x].red +
					img->data[j + (x - 1)].red
					);

				/* GREEN channel of the pixel */
				ggreen = img->data[j].green * 5 - (img->data[j - 1].green +
					img->data[j - x].green +
					img->data[j - x - 1].green + 
					img->data[j + x].green +
					img->data[j + x - 1].green
					);

				/* BLUE channel of the pixel */
				gblue = img->data[j].blue * 5 - (img->data[j - 1].blue +
					img->data[j - x].blue +
					img->data[j - x - 1].blue +
					img->data[j + x].blue +
					img->data[j + x - 1].blue
					);


				/* If a result is larger than the range, adjusts to the maximum value (255) */
				if (gred > 255)		{ gred = 255; }
				if (ggreen > 255)	{ ggreen = 255; }
				if (gblue > 255)	{ gblue = 255; }

				/* If a result is smaller than the range, adjusts to the minimum value (0) */
				if (gred < 0)		{ gred = 0; }
				if (ggreen < 0)		{ ggreen = 0; }
				if (gblue < 0)		{ gblue = 0; }

				/* After adjusted, the value is set on each channel */
				img2->data[j].red = gred;
				img2->data[j].green = ggreen;
				img2->data[j].blue = gblue;
			}


			// # MIDDLE
			else {
				
				j = i;

				/* The pixel is multiplied by 8 and the result is subtracted by its neighbors */

				/* RED channel of the pixel */
				gred = img->data[j].red * 8 - (img->data[j + 1].red +
					img->data[j - 1].red +
					img->data[j + x].red +
					img->data[j + (x - 1)].red +
					img->data[j + (x + 1)].red +
					img->data[j - x].red +
					img->data[j - x - 1].red +
					img->data[j - x + 1].red
					);

				/* GREEN channel of the pixel */
				ggreen = img->data[j].green * 8 - (img->data[j + 1].green +
					img->data[j - 1].green +
					img->data[j + x].green +
					img->data[j + (x - 1)].green +
					img->data[j + (x + 1)].green +
					img->data[j - x].green +
					img->data[j - x - 1].green +
					img->data[j - x + 1].green
					);

				/* BLUE channel of the pixel */
				gblue = img->data[j].blue * 8 - (img->data[j + 1].blue +
					img->data[j - 1].blue +
					img->data[j + x].blue +
					img->data[j + (x - 1)].blue +
					img->data[j + (x + 1)].blue +
					img->data[j - x].blue +
					img->data[j - x - 1].blue +
					img->data[j - x + 1].blue
					);

				/* If a result is larger than the range, adjusts to the maximum value (255) */
				if (gred > 255)		{ gred = 255; }
				if (ggreen > 255)	{ ggreen = 255; }
				if (gblue > 255)	{ gblue = 255; }

				/* If a result is smaller than the range, adjusts to the minimum value (0) */
				if (gred < 0)		{ gred = 0; }
				if (ggreen < 0)		{ ggreen = 0; }
				if (gblue < 0)		{ gblue = 0; }

				/* After adjusted, the value is set on each channel */
				img2->data[j].red = gred;
				img2->data[j].green = ggreen;
				img2->data[j].blue = gblue;

			}

		}
	}
	return img2;
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

		/*  Formula for luminosity: 0.21 R + 0.72 G + 0.07 B.*/
		img2->data[i].gray = (img->data[i].red * 0.21) + (img->data[i].green * 0.72) + (img->data[i].blue * 0.07);


	}
	

	return img2;
}