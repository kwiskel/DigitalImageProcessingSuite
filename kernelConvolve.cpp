////////////////////////////////////////////////
// Name: Kyle Wiskel & Nayan Prakash
// ID #: 1540485 & 1533064
// CMPUT 275, Winter 2019
//
// CMPUT 275 Final Project -- Digital Image Processing Suite
////////////////////////////////////////////////

#include "CImg/CImg.h"
#include "kernelConvolve.h"

using namespace cimg_library;

/*  kernel convolves with kernel of side length n
    Note: n is assumed to be odd

    Arguments:
        CImg<unsigned char> & image: image which will be convoluted

        float kernel[3][3]: 3x3 kernel that will convolve the image

        int n: size of kernel

    Return:
        CImg<unsigned char>: image which has been kernel convoluted
*/
CImg<unsigned char> kernelConvolve(CImg<unsigned char> & image, float kernel[3][3], int n) {
    // create new image of same dimensions as old image
    CImg<unsigned char> newImage(image.width(), image.height(), 1, image.spectrum(), 0);
    // loop through each pixel in image (excluding borders that will not fit
    // a full kernel)
    for (int i = (n-1)/2; i < image.width()-(n-1)/2; i++) {
        for (int j = (n-1)/2; j < image.height()-(n-1)/2; j++) {
            for (int k = 0; k < image.spectrum(); k++) {
                int val = 0;
                // sum the multiplications of the s and t-th value in the
                // kernel with the s and t-th pixel in the n-th neighborhood
                // around current pixel, centered at the current pixel
                for (int a = -1*(n-1)/2; a <= (n-1)/2; a++) {
                    for (int b = -1*(n-1)/2; b <= (n-1)/2; b++) {
                        val += kernel[a+(n-1)/2][b+(n-1)/2]*image(i+a, j+b, 0, k);
                    }
                }
                // assign convoluted pixel value (in correct range of possible
                // pixel values)
                if (val < 0) {
                    newImage(i, j, 0, k) = 0;
                }
                else if (val > 255) {
                    newImage(i, j, 0, k) = 255;
                }
                else {
                    newImage(i, j, 0, k) = val;
                }
            }
        }
    }
    return newImage;
}

CImg<unsigned char> gaussianFilter(CImg<unsigned char>  image, int delta) {

    /* Performs an Guassian filter blue (and noise reduction) on an image. This is done using a specifically weighted kernel 
    and tests for edge cases. When an edge case is found (when the difference between the center pixel and an adjacent pixel is 
    greater than the delta value-->The weight of the adjacent pixel is trasnferred to the center pixel (so the edge doesn't
    affect the value on opposite sides.) )




    Arguments:
        CImg<unsigned char> image --> The image
        int delta --> This is the lower bound for the difference when comparing pixels for edge values
    Return:
        CImg<unsigned char>: Returns the modified image

       
    
    */

    
    // uses a guassian filter and kernel convolution to remove noise from an edge
    // tries to preserve edge values
    int n = 5; // dimensions of kernel
    float sum = 273; // sum of kernel elements
    float kernel[5][5] = {{1,4,7,4,1},{4,16,26,16,4},{7,26,41,26,7},{4,16,26,16,4},{1,4,7,4,1}};
    //int delta = 200; // difference for edge casde
    // find best 5*5 kernel

    CImg<unsigned char> newImage(image.width(), image.height(), 1, image.spectrum(), 0);
    for (int i = (n-1)/2; i < image.width()-(n-1)/2; i++) {
        for (int j = (n-1)/2; j < image.height()-(n-1)/2; j++) {
            for (int k = 0; k < image.spectrum(); k++) {
                int val = 0;
                for (int a = -1*(n-1)/2; a <= (n-1)/2; a++) {
                    for (int b = -1*(n-1)/2; b <= (n-1)/2; b++) {
                        if ((image(i+a,j+b,0,k)) - image(i,j,0,k) >= delta){
                            // if seems like there is an edge
                            val += (kernel[a+(n-1)/2][b+(n-1)/2]/sum)*image(i, j, 0, k);
                        } else {
                            val += (kernel[a+(n-1)/2][b+(n-1)/2]/sum)*image(i+a, j+b, 0, k);
                        }
                    }
                }
                if (val < 0) {
                    newImage(i, j, 0, k) = 0;
                } else if (val > 255) {
                    newImage(i, j, 0, k) = 255;
                } else {
                    newImage(i, j, 0, k) = val;
                }
            }
        }
    }
    return newImage;

}
