#include<stdio.h>
#include<stdlib.h>
#include "PPM.h"

/* Function given by the professor, applies the negative effect in the image */
void changeColorPPM(PPMImage *img)
{
	int i;
	if (img){

		for (i = 0; i<img->x*img->y; i++){
			img->data[i].red	= RGB_COMPONENT_COLOR - img->data[i].red;
			img->data[i].green	= RGB_COMPONENT_COLOR - img->data[i].green;
			img->data[i].blue	= RGB_COMPONENT_COLOR - img->data[i].blue;
		}
	}
}


/* Function to convert a RGB image in a Grayscale - uses the average method */
void changeToGrayScale(PPMImage *img) {
	int i;
	int average;

	if (img){

		/* Go through each pixel of the image */
		for (i = 0; i<img->x*img->y; i++) {
			
			/* Calculates average of the values in each channel (rgb) and 
			set the pixels with the new value */
			average = (img->data[i].red + img->data[i].green + img->data[i].blue) / 3;

			img->data[i].red	= average;
			img->data[i].green	= average;
			img->data[i].blue	= average;

		}
	}
}

/* Function that applies the (3x3) mask 1:
	| -1 | -1 | -1 |
	| -1 |  8 | -1 |	
	| -1 | -1 | -1 | */
void mask1(PPMImage *img)
{
	int i, j;
	int x = img->x;
	int y = img->y;
	int gred, ggreen, gblue;

	if (img){

		/* Go through each pixel of the image */
		for (i = 0; i < img->x*img->y; i++){

			/* Case 1: Top-left pixel */
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
				img->data[j].red = gred;
				img->data[j].green = ggreen;
				img->data[j].blue = gblue;

			}

			/* Case 2: Top line */
			else if (i < (x - 1)) {

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
				img->data[j].red = gred;
				img->data[j].green = ggreen;
				img->data[j].blue = gblue;


			}

			/* Case3: Top-right pixel */
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
				img->data[j].red = gred;
				img->data[j].green = ggreen;
				img->data[j].blue = gblue;


			}

			/* Case4: Right column */
			else if ((i + 1) % x == 0) {

				j = i;

				/* ERROR */

				/* i neighbors 
					i - 1
					i - x
					i - x - 1
					i + x
					i + x - 1
				*/
				

				/* The pixel is multiplied by 5 and the result is subtracted by its neighbors */

				/* RED channel of the pixel */
				gred = img->data[j].red * 5 - (img->data[j - 1].red +
					img->data[j - x].red +
					img->data[j - x - 1].red
					//+ img->data[j + x].red 
					//+ img->data[j + (x - 1)].red
					);

				/* GREEN channel of the pixel */
				ggreen = img->data[j].green * 5 - (img->data[j - 1].green +
													img->data[j - x].green +
													img->data[j - x - 1].green 
													//+ img->data[j + x].green +
													//img->data[j + x - 1].green
													);

				/* BLUE channel of the pixel */
				gblue = img->data[j].blue * 5 - (img->data[j - 1].blue +
													img->data[j - x].blue +
													img->data[j - x - 1].blue 
													//+ img->data[j + x].blue +
													//img->data[j + x - 1].blue
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
				img->data[j].red = gred;
				img->data[j].green = ggreen;
				img->data[j].blue = gblue;
				
			}

			/* Case5: Bottom-right pixel */
			else if (i == (x*y) - 1) {

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
				img->data[j].red = gred;
				img->data[j].green = ggreen;
				img->data[j].blue = gblue;


			}

			/* Case6: Bottom line */
			else if (i > x*(y - 1)) {

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
				img->data[j].red = gred;
				img->data[j].green = ggreen;
				img->data[j].blue = gblue;

			}

			/* Case7: Bottom-left pixel */
			else if (i == (x*(y - 1))) {

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
				img->data[j].red = gred;
				img->data[j].green = ggreen;
				img->data[j].blue = gblue;

			}

			/* Case8: Left column */
			else if (i % x == 0) {
				
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
				img->data[j].red = gred;
				img->data[j].green = ggreen;
				img->data[j].blue = gblue;

			}

			/* Case9: Middle */ 
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
				img->data[j].red = gred;
				img->data[j].green = ggreen;
				img->data[j].blue = gblue;
			}
		}
	}
}


/* Function that applies the (3x3) mask 2:
	| 1 | 2 |  1 |
	| 2 | 4 |  2 |
	| 1 | 2 |  1 | */
void mask2(PPMImage *img)
{
	int i, j;
	int x = img->x;
	int y = img->y;
	int gred, ggreen, gblue;

	if (img){


		/* Go through each pixel of the image */
		for (i = 0; i < img->x*img->y; i++){


			/* Case 1: Top-left pixel */
			if (i == 0) {
				j = i;

				
				/* Multiplies the pixel by 4, the pixels with distance 1 from it are mutiplied by 2,
				the pixels with distance 2 are supposed to be multiplied by 1, but any operation is
				done. Once that is in the border, not all pixels were considered. The result of the 
				operation is divided by 8. */

				/* RED channel of the pixel */
				gred = (
					(img->data[j].red * 4) +

					(img->data[j + 1].red * 2) +
					(img->data[j + x].red * 2 ) +

					img->data[j + (x + 1)].red
					) / 8 ;

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
				img->data[j].red = gred;
				img->data[j].green = ggreen;
				img->data[j].blue = gblue;
				
			}
			
			/* Case 2: Top line */
			else if (i < (x - 1)) {
				
				j = i;

				/* Multiplies the pixel by 4, the pixels with distance 1 from it are mutiplied by 2,
				the pixels with distance 2 are supposed to be multiplied by 1, but any operation is
				done. Once that is in the border, not all pixels were considered. The result of the
				operation is divided by 12. */

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
				img->data[j].red = gred;
				img->data[j].green = ggreen;
				img->data[j].blue = gblue;

			}

			/* Case3: Top-right pixel */
			else if (i == (x - 1)) {
				
				j = i;

				/* Multiplies the pixel by 4, the pixels with distance 1 from it are mutiplied by 2,
				the pixels with distance 2 are supposed to be multiplied by 1, but any operation is
				done. Once that is in the border, not all pixels were considered. The result of the
				operation is divided by 8. */

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
				img->data[j].red = gred;
				img->data[j].green = ggreen;
				img->data[j].blue = gblue;

			}

			/* Case4: Right column */
			else if ((i + 1) % x == 0) {
				j = i;

				/* Multiplies the pixel by 4, the pixels with distance 1 from it are mutiplied by 2,
				the pixels with distance 2 are supposed to be multiplied by 1, but any operation is
				done. Once that is in the border, not all pixels were considered. The result of the
				operation is divided by 12. */

				/* ERROR - instead of neighbors is acessing unallocated positions of memory */
				
				/* i neihbors 
					i - 1
					i - x
					i - x - 1
					i + x
					i + x - 1
				*/

				/* RED channel of the pixel */
				gred = (
					(img->data[j].red * 4) +
					
					(img->data[j - 1].red * 2) +
					(img->data[j - x].red * 2) +
					//(img->data[j + x].red * 2) +

					img->data[j - x - 1].red
					//+ img->data[j + (x - 1)].red
					) / 12;

				/* GREEN channel of the pixel */
				ggreen = (
					(img->data[j].green * 4) +

					(img->data[j - 1].green * 2) +
					(img->data[j - x].green * 2) +
					//(img->data[j + x].green * 2) +

					img->data[j - x - 1].green
					//+ img->data[j + (x - 1)].green
					) / 12;

				/* BLUE channel of the pixel */
				gblue = (
					(img->data[j].blue * 4) +

					(img->data[j - 1].blue * 2) +
					(img->data[j - x].blue * 2) +
					//(img->data[j + x].blue * 2) +

					img->data[j - x - 1].blue
					//+ img->data[j + (x - 1)].blue
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
				img->data[j].red = gred;
				img->data[j].green = ggreen;
				img->data[j].blue = gblue;

			}

			/* Case5: Bottom-right pixel */
			else if (i == (x*y) - 1) {
			
				j = i;

				/* Multiplies the pixel by 4, the pixels with distance 1 from it are mutiplied by 2,
				the pixels with distance 2 are supposed to be multiplied by 1, but any operation is
				done. Once that is in the border, not all pixels were considered. The result of the
				operation is divided by 8. */

				/* RED channel of the pixel */
				gred = (
					(img->data[j].red * 4) +
					
					(img->data[j - 1].red * 2) +
					(img->data[j - x].red * 2) +

					img->data[j - x - 1].red
					) / 8 ;

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
				img->data[j].red = gred;
				img->data[j].green = ggreen;
				img->data[j].blue = gblue;

			}

			/* Case6: Bottom line */
			else if (i > x*(y - 1)) {
				
				j = i;

				/* Multiplies the pixel by 4, the pixels with distance 1 from it are mutiplied by 2,
				the pixels with distance 2 are supposed to be multiplied by 1, but any operation is
				done. Once that is in the border, not all pixels were considered. The result of the
				operation is divided by 12. */

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
				img->data[j].red = gred;
				img->data[j].green = ggreen;
				img->data[j].blue = gblue;
			
			}

			/* Case7: Bottom-left pixel */
			else if (i == (x*(y - 1))) {

				j = i;

				/* Multiplies the pixel by 4, the pixels with distance 1 from it are mutiplied by 2,
				the pixels with distance 2 are supposed to be multiplied by 1, but any operation is
				done. Once that is in the border, not all pixels were considered. The result of the
				operation is divided by 8. */

				/* RED channel of the pixel */
				gred = (
					(img->data[j].red * 4) +
					(img->data[j + 1].red * 2)+
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
				img->data[j].red = gred;
				img->data[j].green = ggreen;
				img->data[j].blue = gblue;
			}

			/* Case8: Left column */
			else if (i % x == 0) {

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
				img->data[j].red = gred;
				img->data[j].green = ggreen;
				img->data[j].blue = gblue;
			}

			/* Case9: Middle */
			else {

				/* Multiply the pixel by 4, the pixels with distance 1 from it are mutiplied by 2,
				the pixels with distance 2 are supposed to be multiplied by 1, but any operation is
				done. The result is divided by 15. */

				j = i;

				/* RED channel of the pixel */
				gred =	(	
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
				img->data[j].red = gred;
				img->data[j].green = ggreen;
				img->data[j].blue = gblue;
		
			}

		}
	}



}


int main(){
	PPMImage *image, *image2, *image3, *image4, *image5, *image6;
	image = readPPM("original.ppm");
	changeColorPPM(image);
	writePPM("negative.ppm", image);
	
	/* Original to Grayscale*/
	image2 = readPPM("original.ppm");
	changeToGrayScale(image2);
	writePPM("grayscale.ppm", image2);

	/* Original image with Mask 1*/
	image3 = readPPM("original.ppm");
	mask1(image3);
	writePPM("filter1.ppm", image3);

	/* Grayscale image with Mask 1*/
	image4 = readPPM("grayscale.ppm");
	mask1(image4);
	writePPM("filter1-gray.ppm", image4);

	/* Original image with Mask 2*/
	image5 = readPPM("original.ppm");
	mask2(image5);
	writePPM("filter2.ppm", image5);

	/* Grayscale image with Mask 2*/
	image6 = readPPM("grayscale.ppm");
	mask2(image6);
	writePPM("filter2-gray.ppm", image6);

	printf("Press any key...");
	getchar();
}