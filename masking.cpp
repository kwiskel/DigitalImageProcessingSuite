////////////////////////////////////////////////
// Name: Kyle Wiskel & Nayan Prakash
// ID #: 1540485 & 1533064
// CMPUT 275, Winter 2019
//
// CMPUT 275 Final Project -- Digital Image Processing Suite
////////////////////////////////////////////////

#include "CImg/CImg.h"
#include "masking.h"

using namespace cimg_library;

/* erodes image in an n-sized neighborhood around each pixel

    Arguments:
        CImg<unsigned char> & image: image on which erosion will be done

        int n: size of pixel neighborhood which will be eroded

    Return:
        CImg<unsigned char>: CImg image on which erosion was done
*/
CImg<unsigned char> erosion(CImg<unsigned char> & image, int n) {
    // create new image on which erosion will be done
    CImg<unsigned char> newImage(image.width(), image.height(), 1, image.spectrum());
    // loop through each pixel in image
    for (int i = (n-1)/2; i < image.width()-(n-1)/2; i++) {
        for (int j = (n-1)/2; j < image.height()-(n-1)/2; j++) {
            for (int k = 0; k < image.spectrum(); k++) {
                // find smallest value pixel in n-size neighborhood around
                // current pixel
                unsigned char val = image(i, j, 0, k);
                for (int a = -1*(n-1)/2; a <= (n-1)/2; a++) {
                    for (int b = -1*(n-1)/2; b <= (n-1)/2; b++) {
                        if (i+a < image.width() && i+a >= 0 && j+b < image.height() && j+b >= 0) {
                            if (image(i+a, j+b, 0, k) < val) val = image(i+a, j+b, 0, k);
                        }
                    }
                }
                // assign pixel to lowest pixel value in neighborhood
                newImage(i, j, 0, k) = val;
            }
        }
    }
    return newImage;
}

/* dilates image in an n-sized neighborhood around each pixel

    Arguments:
        CImg<unsigned char> & image: image on which dilation will be done

        int n: size of pixel neighborhood which will be dilated

    Return:
        CImg<unsigned char>: CImg image on which dilation was done
*/
CImg<unsigned char> dilation(CImg<unsigned char> & image, int n) {
    // create new image on which dilation will be done
    CImg<unsigned char> newImage(image.width(), image.height(), 1, image.spectrum());
    // loop through each pixel in image
    for (int i = (n-1)/2; i < image.width()-(n-1)/2; i++) {
        for (int j = (n-1)/2; j < image.height()-(n-1)/2; j++) {
            for (int k = 0; k < image.spectrum(); k++) {
                // find largest value pixel in n-size neighborhood around
                // current pixel
                unsigned char val = image(i, j, 0, k);
                for (int a = -1*(n-1)/2; a <= (n-1)/2; a++) {
                    for (int b = -1*(n-1)/2; b <= (n-1)/2; b++) {
                        if (i+a < image.width() && i+a >= 0 && j+b < image.height() && j+b >= 0) {
                            if (image(i+a, j+b, 0, k) > val) val = image(i+a, j+b, 0, k);
                        }
                    }
                }
                // assign pixel to largest pixel value in neighborhood
                newImage(i, j, 0, k) = val;
            }
        }
    }
    return newImage;
}

/*
    Helper function for pixelate function. Finds pixel value of n possible
    options scaled across range 0-255

    Arguments:
        unsigned char val: pixel value on which nearest quantized value will
            be found

        int n: amount of possible quantized values

    Returns:
        unsigned char: quantized pixel value of val
*/
unsigned char findNearestVal(unsigned char val, int n) {
    // delta value that will be minimized
    unsigned char delta = 255;
    unsigned char discreteValue = 0;
    // divide range 0-255 into n possible options and find n-th value across
    // range closest to val
    for (int i = 0; i <= n; i++) {
        if (abs(255.0/n*i - val) < delta) {
            delta = abs(255.0/n*i - val);
            discreteValue = 255.0/n*i;
        }
    }
    // return closest n-th value to val
    return discreteValue;
}

/* pixelate image into n size squares with 2^c possible colors

    Arguments:
        CImg<unsigned char> & image: image on which pixelation will be done

        int n: size of superpixel that will be assigned

        int c: number of possible colors that each color channel can be
            assigned to

    Return:
        None.
*/
void pixelate(CImg<unsigned char> & image, int n, int c) {
    // loop through each n-by-n superpixel in image
    for (int i = (n-1)/2; i < image.width(); i += n) {
        for (int j = (n-1)/2; j < image.height(); j += n) {
            for (int k = 0; k < image.spectrum(); k++) {
                // quantize pixel value at center of superpixel to one of c
                // possible values
                unsigned char pixelatedVal = findNearestVal(image(i, j, 0, k), c);
                // assign each pixel in superpixel to quantized pixel value
                for (int a = -1*(n-1)/2; a <= (n-1)/2; a++) {
                    for (int b = -1*(n-1)/2; b <= (n-1)/2; b++) {
                        if (i+a < image.width() && i+a >= 0 && j+b < image.height() && j+b >= 0) {
                            image(i+a, j+b, 0, k) = pixelatedVal;
                        }
                    }
                }
            }
        }
    }
}
