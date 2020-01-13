////////////////////////////////////////////////
// Name: Kyle Wiskel & Nayan Prakash
// ID #: 1540485 & 1533064
// CMPUT 275, Winter 2019
//
// CMPUT 275 Final Project -- Digital Image Processing Suite
////////////////////////////////////////////////

#ifndef _HSLMODIFICATION_H_
#define _HSLMODIFICATION_H_

#include "CImg/CImg.h"
using namespace cimg_library;



// modifies the saturation of an image
void changeSaturation(CImg<unsigned char> & image, double satScale);

// modifies the contrast and brightness of the image
void changeBrightness(CImg<unsigned char> & image, double contrast, double brightness);

// converts the RGB pixel to HSL values
void RGB2HSL(unsigned char r, unsigned char g, unsigned char b, unsigned char& h, unsigned char& s, unsigned char& l);

// converts the HSL pixel to RGB values
void HSL2RGB(unsigned char h, unsigned char s, unsigned char l, unsigned char& r, unsigned char& g, unsigned char& b);

// performs tests to modularize conversion from HSL to RGB
double colourTest(double tempC, double temp1, double temp2);


#endif