#include<stdio.h>
#include<stdlib.h>
#include "PPM.h"


int main(){
	PPMImage *image, *image1, *image2;
	PPMGrayImage *image10, *image11, *image12;

	PPMImage *image0, *image01, *image02;
	PPMGrayImage *image010, *image011, *image012;

	/* ********* ORIGINAL IMAGE: *********** */

	image = readPPM("original.ppm");
	
	/* Grayscale */
	image10 = CreateEmptyGrayImageFromColorImage(image);
	image10 = ConvertToGrayFromColorImage(image);
	writeGrayPPM("grayscale.ppm", image10);

	/* Mask 1 - Color */
	image1 = CreateEmptyImage(image);
	image1 = Filter1Color(image);
	writePPM("filter1-color.ppm", image1);

	/* Mask 1 - Grayscale */
	image11 = CreateEmptyGrayImage(image10);
	image11 = Filter1Gray(image10);
	writeGrayPPM("filter1-gray.ppm", image11);

	/* Mask 2 - Color */
	image2 = CreateEmptyImage(image);
	image2 = Filter2Color(image);
	writePPM("filter2-color.ppm", image2);

	/* Mask 2 - Grayscale */
	image12 = CreateEmptyGrayImage(image10);
	image12 = Filter2Gray(image10);
	writeGrayPPM("filter2-gray.ppm", image12);


	/* *********** TEST-CASE: *********** */

	image0 = readPPM("MoM Bldg.ppm");

	/* Grayscale */
	image010 = CreateEmptyGrayImageFromColorImage(image0);
	image010 = ConvertToGrayFromColorImage(image0);
	writeGrayPPM("MoM Bldgg grayscale.ppm", image010);

	/* Mask 1 - Color */
	image01 = CreateEmptyImage(image0);
	image01 = Filter1Color(image0);
	writePPM("MoM Bldg filter1-color.ppm", image01);

	/* Mask 1 - Grayscale */
	image011 = CreateEmptyGrayImage(image010);
	image011 = Filter1Gray(image010);
	writeGrayPPM("MoM Bldg filter1-gray.ppm", image011);

	/* Mask 2 - Color */
	image02 = CreateEmptyImage(image0);
	image02 = Filter2Color(image0);
	writePPM("MoM Bldg filter2-color.ppm", image02);

	/* Mask 2 - Grayscale  */
	image012 = CreateEmptyGrayImage(image010);
	image012 = Filter2Gray(image010);
	writeGrayPPM("MoM Bldg filter2-gray.ppm", image012);


	printf("Done. Press Enter...");
	getchar();
}