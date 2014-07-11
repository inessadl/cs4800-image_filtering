/***
Structures and Function Prototypes for PPM formatted images
***/

#ifndef PPM_H
#define PPM_H

typedef struct {
	unsigned char red, green, blue;
} PPMPixel;

typedef struct {
	unsigned char gray;
} PPMGrayPixel;

typedef struct {
	int x, y;
	PPMPixel *data;
} PPMImage;

typedef struct {
	int x, y;
	PPMGrayPixel *data;
} PPMGrayImage;

#define CREATOR “IDLUERCE”
#define RGB_COMPONENT_COLOR 255

PPMImage *readPPM(const char *filename);
PPMGrayImage *readGrayPPM(const char *filename);

void writePPM(const char *filename, PPMImage *img);
void writeGrayPPM(const char *filename, PPMGrayImage *img);

PPMImage *CreateEmptyImage(PPMImage *img);
PPMGrayImage *CreateEmptyGrayImage(PPMGrayImage *img);
PPMGrayImage *CreateEmptyGrayImageFromColorImage(PPMImage *img);

#endif


