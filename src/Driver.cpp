#include<stdio.h>
#include<stdlib.h>
#include "PPM.h"


/* Function given by the professor, applies the negative effect in the image */
void changeColorPPM(PPMImage *img)
{
	int i;
	if (img){

		for (i = 0; i<img->x*img->y; i++){
			img->data[i].red = RGB_COMPONENT_COLOR - img->data[i].red;
			img->data[i].green = RGB_COMPONENT_COLOR - img->data[i].green;
			img->data[i].blue = RGB_COMPONENT_COLOR - img->data[i].blue;
		}
	}
}



int main(){
	PPMImage *image, *image2, *image3, *image4, *image5, *image6, *image7;
	PPMGrayImage *image11;

	/* just for test, comment or delete after that */
	image = readPPM("original.ppm");
	//changeColorPPM(image);
	//writePPM("negative.ppm", image); // delete it


	/* 3 Creates an empty grayscale ppm and apply the grayscale formula in the original image */
	//image3 = CreateEmptyGrayImage;
	image11 = CreateEmptyGrayImageFromColorImage(image);
	// convert here?
	image11 = ConvertToGrayFromColorImage(image);
	writeGrayPPM("original-grayscale.ppm", image11);

	/* 4 Creates a new image and copies the original */
	image2 = CreateEmptyImage(image);
	image2 = readPPM("original.ppm");
	writePPM("test.ppm", image2);

	/* Applies the first mask in the colored image */
	image2 = mask1(image);
	writePPM("mask1-color.ppm", image2);

	//image2 = mask1(image);

	/* 
	1) open original

	2) create an empty colored (image2)
	3) create an empty grayscale (image3)
	3) transform the img3 in grayscale with a formula
	
	4) create an empty colored (img4)
	5) apply mask1 (based on the original)
	6) create an empty colored (img5)
	7) apply mask2 (based on the original)

	8) create and empty grayscale (img6)
	9) apply mask1 (based on the original grayscale)
	10) create and empty grayscale (img7)
	11) apply mask2 (based on the original grayscale)

	*/


	printf("Sucessully executed. Press enter...");
	getchar();
}