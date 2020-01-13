////////////////////////////////////////////////
// Name: Kyle Wiskel & Nayan Prakash
// ID #: 1540485 & 1533064
// CMPUT 275, Winter 2019
//
// CMPUT 275 Final Project -- Digital Image Processing Suite
////////////////////////////////////////////////

#ifndef _KERNELCONVOLVE_H_
#define _KERNELCONVOLVE_H_

#include "CImg/CImg.h"
using namespace cimg_library;

// convolves image with given kernel
CImg<unsigned char> kernelConvolve(CImg<unsigned char> & image, float kernel[3][3], int n);

// convolves an image with a specified weigthed kernel and preserved edge values
CImg<unsigned char> gaussianFilter(CImg<unsigned char>  image, int delta);

#endif
