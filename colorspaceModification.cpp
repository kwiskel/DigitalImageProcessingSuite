////////////////////////////////////////////////
// Name: Kyle Wiskel & Nayan Prakash
// ID #: 1540485 & 1533064
// CMPUT 275, Winter 2019
//
// CMPUT 275 Final Project -- Digital Image Processing Suite
////////////////////////////////////////////////

#include "CImg/CImg.h"
#include "colorspaceModification.h"

using namespace cimg_library;

/*
    function to convert image to grayscale

    Arguments:
        CImg<unsigned char> & image: CImg image which will be converted to
            grayscale

    Return:
        CImg<unsigned char>: returns the grayscale converted image
*/
CImg<unsigned char> toGrayscale(CImg<unsigned char> & image) {
    /* create new image of colour depth one */
    CImg<unsigned char> newImage(image.width(), image.height(), 1, 1);
    /* for every pixel in old image set the pixel in the new image to the
       mean value of all color values in old image  */
    for (int j = 1; j < image.height()-1; j++) {
        for (int i = 1; i < image.width()-1; i++) {
            int sum = image(i, j, 0, 0) + image(i, j, 0, 1) + image(i, j, 0, 2);
            sum = sum / 3;
            newImage(i, j, 0, 0) = sum;
        }
    }
    return newImage;
}
