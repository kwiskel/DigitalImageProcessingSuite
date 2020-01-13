////////////////////////////////////////////////
// Name: Kyle Wiskel & Nayan Prakash
// ID #: 1540485 & 1533064
// CMPUT 275, Winter 2019
//
// CMPUT 275 Final Project -- Digital Image Processing Suite
////////////////////////////////////////////////

#include "CImg/CImg.h"
#include "dithering.h"

using namespace cimg_library;

/*
    Helper function for halftoneDithering function. Finds which mask option
    will be applied to 5x5 image superpixel depending on value of pixel
    centered in 5x5 superpixel
    Note: there are only 7 possible levels of mask options

    Arguments:
        unsigned char val: value of pixel in center of 5x5 superpixel

    Returns:
        int: value 0-6 represents the halftone mask option. The higher the
            value, the larger the applied mask will be
*/
int findHalftoneOption(unsigned char val) {
    unsigned char delta = 255;
    int option = 7;
    for (int i = 0; i <= 6; i++) {
        if (abs(255.0/7*i - val) < delta) {
            delta = abs(255.0/7*i - val);
            option = i;
        }
    }
    return option;
}

/*
    Helper function for halftoneDithering function. Applies halftone mask
    to 5x5 superpixel of image

    Arguments:
        CImg<unsigned char> & image: image on which mask will be applied

        int x: x position at which 5x5 superpixel is centered

        int y: y positon at which 5x5 superpixel is centered

        int c: color channel at which mask is being applied

        unsigned char halftone[5][5]: 5x5 halftone mask to apply to superpixel

    Return:
        None.
*/
void setHalftone(CImg<unsigned char> & image, int x, int y, int c, unsigned char halftone[5][5]) {
    for (int a = -2; a <= 2; a++) {
        for (int b = -2; b <= 2; b++) {
            if (x+a < image.width() && x+a >= 0 && y+b < image.height() && y+b >= 0) {
                image(x+a, y+b, 0, c) = halftone[a+2][b+2];
            }
        }
    }
}

/*
    Does helftone dithering on image in 5x5 circular shapes

    Arguments:
        CImg<unsigned char> & image: image on which halftone dithering
            will be done

    Return:
        None.
*/
void halftoneDithering(CImg<unsigned char> & image) {
    // use for loop on color depth to offset separate color channels to be
    // centered at different x, y positions on image
    for (int k = 0; k < image.spectrum(); k++) {
        // for every 5x5 superpixel of image calculate halftone and apply
        // halftone mask
        for (int i = 2+k*2; i < image.width(); i+=5) {
            for (int j = 2+k; j < image.height(); j+=5) {
                // assign mask depending on calculated halftone mask option
                switch(findHalftoneOption(image(i, j, 0, k))) {
                    case 0:
                    {
                        unsigned char halftone[5][5] = {{0, 0, 0, 0, 0},
                                    {0, 0, 0, 0, 0},
                                    {0, 0, 0, 0, 0},
                                    {0, 0, 0, 0, 0},
                                    {0, 0, 0, 0, 0}};
                        setHalftone(image, i, j, k, halftone);
                        break;
                    }
                    case 1:
                    {
                        unsigned char halftone[5][5] = {{255, 0, 0, 0, 255},
                                    {0, 0, 0, 0, 0},
                                    {0, 0, 0, 0, 0},
                                    {0, 0, 0, 0, 0},
                                    {255, 0, 0, 0, 255}};
                        setHalftone(image, i, j, k, halftone);
                        break;
                    }
                    case 2:
                    {
                        unsigned char halftone[5][5] = {{255, 255, 0, 255, 255},
                                    {255, 0, 0, 0, 255},
                                    {0, 0, 0, 0, 0},
                                    {255, 0, 0, 0, 255},
                                    {255, 255, 0, 255, 255}};
                        setHalftone(image, i, j, k, halftone);
                        break;
                    }
                    case 3:
                    {
                        unsigned char halftone[5][5] = {{255, 255, 255, 255, 255},
                                    {255, 0, 0, 0, 255},
                                    {255, 0, 0, 0, 255},
                                    {255, 0, 0, 0, 255},
                                    {255, 255, 255, 255, 255}};
                        setHalftone(image, i, j, k, halftone);
                        break;
                    }
                    case 4:
                    {
                        unsigned char halftone[5][5] = {{255, 255, 255, 255, 255},
                                    {255, 255, 0, 255, 255},
                                    {255, 0, 0, 0, 255},
                                    {255, 255, 0, 255, 255},
                                    {255, 255, 255, 255, 255}};
                        setHalftone(image, i, j, k, halftone);
                        break;
                    }
                    case 5:
                    {
                        unsigned char halftone[5][5] = {{255, 255, 255, 255, 255},
                                    {255, 255, 255, 255, 255},
                                    {255, 255, 0, 255, 255},
                                    {255, 255, 255, 255, 255},
                                    {255, 255, 255, 255, 255}};
                        setHalftone(image, i, j, k, halftone);
                        break;
                    }
                    case 6:
                    {
                        unsigned char halftone[5][5] = {{255, 255, 255, 255, 255},
                                    {255, 255, 255, 255, 255},
                                    {255, 255, 255, 255, 255},
                                    {255, 255, 255, 255, 255},
                                    {255, 255, 255, 255, 255}};
                        setHalftone(image, i, j, k, halftone);
                        break;
                    }
                    default:
                    {
                        unsigned char halftone[5][5] = {{0, 0, 0, 0, 0},
                                    {0, 0, 0, 0, 0},
                                    {0, 0, 0, 0, 0},
                                    {0, 0, 0, 0, 0},
                                    {0, 0, 0, 0, 0}};
                        setHalftone(image, i, j, k, halftone);
                        break;
                    }
                }
            }
        }
    }
}

/*
    helper function for floydSteinberg function. returns 0 or 255 to quantize
    given value

    Arguments:
        unsigned char val: pixel value to quantize to either 0 or 255,
            depending on whichever val is closest to

    Return:
        unsigned char: quantized pixel value
*/
unsigned char quantize(unsigned char val) {
    return round(val / 255.0)*255;
}

/*  Does floyd-steinberg dithering on image and dithers up to 2^n
    discrete colour values where n is the color depth of the image

    Note: This follows the pseudocode given on:
    https://en.wikipedia.org/wiki/Floyd%E2%80%93Steinberg_dithering

    Arguments:
        CImg<unsigned char> & image: CImg image on which floyd-steinberg
            dithering will be done

    Returns:
        None

*/
void floydSteinberg(CImg<unsigned char> & image) {
    for (int j = 1; j < image.height()-1; j++) {
        for (int i = 1; i < image.width()-1; i++) {
            // create unsigned char arrays as large as the images color depth
            // for old and new pixel values as well as error value
            unsigned char oldPixel[image.spectrum()];
            unsigned char newPixel[image.spectrum()];
            unsigned char quantError[image.spectrum()];
            // for each color channel of current pixel, quantize pixel
            // and propage error in old pixel value and quantized value
            // further ahead in image
            for (int k = 0; k < image.spectrum(); k++) {
                oldPixel[k] = image(i, j, 0, k);
                // quantize and assign pixel value
                newPixel[k] = quantize(oldPixel[k]);
                image(i, j, 0, k) = 255-newPixel[k];
                // calculate error between current new and old pixel values
                quantError[k] = oldPixel[k] - newPixel[k];
                // propogate error in dithered pixel to pixels ahead of
                // current pixel
                image(i + 1, j    , 0, k) = image(i + 1, j    , 0, k) + quantError[k] * 7.0 / 16.0;
                image(i - 1, j + 1, 0, k) = image(i - 1, j + 1, 0, k) + quantError[k] * 3.0 / 16.0;
                image(i    , j + 1, 0, k) = image(i    , j + 1, 0, k) + quantError[k] * 5.0 / 16.0;
                image(i + 1, j + 1, 0, k) = image(i + 1, j + 1, 0, k) + quantError[k] * 1.0 / 16.0;
            }
        }
    }
}
