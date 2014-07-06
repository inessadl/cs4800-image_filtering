/***
Structures and Function Prototypes for PPM formatted images
***/

typedef struct {
	unsigned char red, green, blue;
} PPMPixel;

typedef struct {
	int x, y;
	PPMPixel *data;
} PPMImage;

#define CREATOR "IDLUERCE"
#define RGB_COMPONENT_COLOR 255

PPMImage *readPPM(const char *filename);
void writePPM(const char *filename, PPMImage *img);

