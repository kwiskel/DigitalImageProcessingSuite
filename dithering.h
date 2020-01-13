////////////////////////////////////////////////
// Name: Kyle Wiskel & Nayan Prakash
// ID #: 1540485 & 1533064
// CMPUT 275, Winter 2019
//
// CMPUT 275 Final Project -- Digital Image Processing Suite
////////////////////////////////////////////////

#ifndef _DITHERING_H_
#define _DITHERING_H_

#include "CImg/CImg.h"
using namespace cimg_library;

// finds which option of masks should be applied to 5x5 superpixel
int findHalftoneOption(unsigned char val);

// sets 5x5 halftone mask to image
void setHalftone(CImg<unsigned char> & image, int x, int y, int c, unsigned char halftone[5][5]);

// does halftone dithering on image
void halftoneDithering(CImg<unsigned char> & image);

// returns 0 or 255, whichever val is closest to
unsigned char quantize(unsigned char val);

// does floyd-steinberg dithering on image
void floydSteinberg(CImg<unsigned char> & image);

#endif
