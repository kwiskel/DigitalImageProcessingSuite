////////////////////////////////////////////////
// Name: Kyle Wiskel & Nayan Prakash
// ID #: 1540485 & 1533064
// CMPUT 275, Winter 2019
//
// CMPUT 275 Final Project -- Digital Image Processing Suite
////////////////////////////////////////////////

#ifndef _FOURIER_H_
#define _FOURIER_H_

#include "CImg/CImg.h"
#include <complex>
#include <vector>
using namespace cimg_library;


// performs the FFT transform on a vector representing the image pixels
std::vector<std::complex<double>> fastFourierTransform(std::vector<std::complex<double>>& values);

// performs the slow fourier transform on an image file
void slowFourierTransform(CImg<unsigned char> image);

// transforms the image to a vector then performs FFT then performs reverse FFT and compares original to reversed
void fourierRepresentation(CImg<unsigned char> image);

#endif