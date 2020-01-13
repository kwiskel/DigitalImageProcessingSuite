////////////////////////////////////////////////
// Name: Kyle Wiskel & Nayan Prakash
// ID #: 1540485 & 1533064
// CMPUT 275, Winter 2019
//
// CMPUT 275 Final Project -- Digital Image Processing Suite
////////////////////////////////////////////////

#ifndef _COLORSPACEMODIFICATION_H_
#define _COLORSPACEMODIFICATION_H_

#include "CImg/CImg.h"
using namespace cimg_library;

// converts image to grayscale
CImg<unsigned char> toGrayscale(CImg<unsigned char> & image);

#endif
