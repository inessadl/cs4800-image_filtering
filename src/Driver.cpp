#include<stdio.h>
#include<stdlib.h>
#include "PPM.h"


void changeColorPPM(PPMImage *img)
{
	int i;
	if (img){

		for (i = 0; i<img->x*img->y; i++){
			img->data[i].red 	= RGB_COMPONENT_COLOR - img->data[i].red;
			img->data[i].green 	= RGB_COMPONENT_COLOR - img->data[i].green;
			img->data[i].blue 	= RGB_COMPONENT_COLOR - img->data[i].blue;
		}
	}
}

void changeColor (PPMImage *img) {

}

/* using the average method*/
void changeToGrayScale(PPMImage *img) {
	int i;
	int average;

	if (img){

		for (i = 0; i<img->x*img->y; i++){
			
			average = (img->data[i].red + img->data[i].green + img->data[i].blue) / 3;

			img->data[i].red = average;
			img->data[i].green = average;
			img->data[i].blue = average;
		}
	}
}

int main(){
	PPMImage *image;
	image = readPPM("luerce1.ppm");
	changeColorPPM(image);
	writePPM("luerce2.ppm", image);
	/*
	changeColor(image);
	writePPM("luerce3.ppm", image);
	*/
	changeToGrayScale(image);
	writePPM("luerce4.ppm", image);
	printf("Press any key...");
	getchar();
}