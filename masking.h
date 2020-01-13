////////////////////////////////////////////////
// Name: Kyle Wiskel & Nayan Prakash
// ID #: 1540485 & 1533064
// CMPUT 275, Winter 2019
//
// CMPUT 275 Final Project -- Digital Image Processing Suite
////////////////////////////////////////////////

#ifndef _MASKING_H_
#define _MASKING_H_

#include "CImg/CImg.h"
using namespace cimg_library;

// erodes image
CImg<unsigned char> erosion(CImg<unsigned char> & image, int n);

// dilates image
CImg<unsigned char> dilation(CImg<unsigned char> & image, int n);

// finds nearets of n options to apply as value for pixelation superpixel
unsigned char findNearestVal(unsigned char val, int n);

// pixelates image into n-sized superpixels with 2^c possible colors
void pixelate(CImg<unsigned char> & image, int n, int c);

#endif
