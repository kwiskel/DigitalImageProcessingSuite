////////////////////////////////////////////////
// Name: Kyle Wiskel & Nayan Prakash
// ID #: 1540485 & 1533064
// CMPUT 275, Winter 2019
//
// CMPUT 275 Final Project -- Digital Image Processing Suite
////////////////////////////////////////////////


#include "CImg/CImg.h"
#include <string>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <complex>
#include <vector>
#include "hslModification.h"
#include "fourier.h"
#include "kernelConvolve.h"
#include "masking.h"
#include "dithering.h"
#include "colorspaceModification.h"

using namespace cimg_library;

int main() {
    bool runAgain = true;
    std::cout << "Welcome to the Digital Image Processing Suite" << std::endl;
    while (runAgain) {
        try{
            // get filename and load in image with corresponding filename
            std::string str;
            std::cout << "Please enter the image filename:" << std::endl;
            std::cin >> str;
            auto filename(str.c_str());
            // original image to compare to
            CImg<unsigned char> image(filename);
            // image that will be processed
            CImg<unsigned char> image2(filename);
            // image used to allow undo-ing of edits
            CImg<unsigned char> image3(filename);
            // image used to append processed image to for comparisons to
            // original image
            CImg<unsigned char> image4(filename);
            bool flag = true;
            while (flag) {
                std::cout << "Please enter how you would like to process the image:" << std::endl;
                std::cout << "1. Dithering" << std::endl;
                std::cout << "2. Masking" << std::endl;
                std::cout << "3. Kernel Convolving" << std::endl;
                std::cout << "4. Value Editing" << std::endl;
                std::cout << "5. Colorspace Converting" << std::endl;
                std::cout << "6. Fast Fourier transform + Fast Inverse Fourier Transform" << std::endl;
                std::cout << "7. Display Latest Edit" << std::endl;
                std::cout << "8. Undo Previous Edit" << std::endl;
                std::cout << "9. Quit" << std::endl;
                // get user image processing option
                int option;
                std::cin >> option;
                switch (option) {
                    case 1:
                    {
                        // user about to further process image so set undo
                        // image to current processed image
                        image3 = image2;
                        std::cout << "Please enter what type of dithering you would like:" << std::endl;
                        std::cout << "1. Floyd-Steinberg Dithering" << std::endl;
                        std::cout << "2. Halftone Dithering" << std::endl;
                        // get user dithering option and do corresponding
                        // dithering on image
                        int option2;
                        std::cin >> option2;
                        switch (option2) {
                            case 1:
                            {
                                floydSteinberg(image2);
                                break;
                            }
                            case 2:
                            {
                                halftoneDithering(image2);
                                break;
                            }
                            default:
                            {
                                std::cout << "Please enter only valid options" << std::endl;
                                break;
                            }
                        }
                        break;
                    }
                    case 2:
                    {
                        // user about to further process image so set undo
                        // image to current processed image
                        image3 = image2;
                        std::cout << "Please enter what type of masking you would like:" << std::endl;
                        std::cout << "1. Pixelation" << std::endl;
                        std::cout << "2. Erosion" << std::endl;
                        std::cout << "3. Dilation" << std::endl;
                        // get user masking option and do corresponding
                        // masking on image
                        int option2;
                        std::cin >> option2;
                        switch (option2) {
                            case 1:
                            {
                                // get user mask size
                                int n;
                                while (true) {
                                    std::cout << "Please enter mask size (must be odd): ";
                                    std::cin >> n;
                                    if (n % 2 == 1) {
                                        break;
                                    } else {
                                        std::cout << "Please enter only valid values" << std::endl;
                                    }
                                }
                                // get user color options
                                int c;
                                while (true) {
                                    std::cout << "Please enter 2^n possible color combinations (between 1 and 8): ";
                                    std::cin >> c;
                                    if (c >= 1 && c <= 8) {
                                        break;
                                    } else {
                                        std::cout << "Please enter only valid values" << std::endl;
                                    }
                                }
                                pixelate(image2, n, c);
                                break;
                            }
                            case 2:
                            {
                                // get user mask size
                                int n;
                                while (true) {
                                    std::cout << "Please enter mask size (must be odd): ";
                                    std::cin >> n;
                                    if (n % 2 == 1) {
                                        break;
                                    } else {
                                        std::cout << "Please enter only valid values" << std::endl;
                                    }
                                }
                                image2 = erosion(image2, n);
                                break;
                            }
                            case 3:
                            {
                                // get user mask size
                                int n;
                                while (true) {
                                    std::cout << "Please enter mask size (must be odd): ";
                                    std::cin >> n;
                                    if (n % 2 == 1) {
                                        break;
                                    } else {
                                        std::cout << "Please enter only valid values" << std::endl;
                                    }
                                }
                                image2 = dilation(image2, n);
                                break;
                            }
                            default:
                            {
                                std::cout << "Please enter only valid options" << std::endl;
                                break;
                            }
                        }
                        break;
                    }
                    case 3:
                    {
                        // user about to further process image so set undo
                        // image to current processed image
                        image3 = image2;
                        std::cout << "Please enter what type of Kernal Convolution you would like:" << std::endl;
                        std::cout << "1. Box Blur" << std::endl;
                        std::cout << "2. Gaussian Blur" << std::endl;
                        std::cout << "3. Edge Detection A" << std::endl;
                        std::cout << "4. Edge Detection B" << std::endl;
                        std::cout << "5. Edge Detection C" << std::endl;
                        std::cout << "6. Sharpen" << std::endl;
                        std::cout << "7. Emboss" << std::endl;
                        std::cout << "8. Gaussian Filtering" << std::endl;
                        // get user kernel convolution option, instantiate
                        // corresponding kernel and kernel convolve
                        // image with kernel
                        int option2;
                        std::cin >> option2;
                        switch (option2) {
                            case 1:
                            {
                                // instantiate kernel for box blur
                                float kernel[3][3] = {{1.0/9, 1.0/9, 1.0/9}, {1.0/9, 1.0/9, 1.0/9}, {1.0/9, 1.0/9, 1.0/9}};
                                image2 = kernelConvolve(image2, kernel, 3);
                                break;
                            }
                            case 2:
                            {
                                // instantiate kernel for gaussian blur
                                float kernel[3][3] = {{1.0/16, 2.0/16, 1.0/16}, {2.0/16, 4.0/16, 2.0/16}, {1.0/16, 2.0/16, 1.0/16}};
                                image2 = kernelConvolve(image2, kernel, 3);
                                break;
                            }
                            case 3:
                            {
                                // instantiate kernel for Edge Detection A
                                float kernel[3][3] = {{1, 0, -1}, {0, 0, 0}, {-1, 0, 1}};
                                image2 = kernelConvolve(image2, kernel, 3);
                                break;
                            }
                            case 4:
                            {
                                // instantiate kernel for Edge Detection B
                                float kernel[3][3] = {{0, 1, 0}, {1, -4, 1}, {0, 1, 0}};
                                image2 = kernelConvolve(image2, kernel, 3);
                                break;
                            }
                            case 5:
                            {
                                // instantiate kernel for Edge Detection C
                                float kernel[3][3] = {{-1, -1, -1}, {-1, 8, -1}, {-1, -1, -1}};
                                image2 = kernelConvolve(image2, kernel, 3);
                                break;
                            }
                            case 6:
                            {
                                // instantiate kernel for sharpening
                                float kernel[3][3] = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};
                                image2 = kernelConvolve(image2, kernel, 3);
                                break;
                            }
                            case 7:
                            {
                                // instantiate kernel for embossing
                                float kernel[3][3] = {{-1, -1, 0}, {-1, 0, 1}, {0, 1, 1}};
                                image2 = kernelConvolve(image2, kernel, 3);
                                break;
                            }
                            case 8:
                            {
                                // get user delta option
                                int delta;
                                std::cout << "Please enter delta value for Guassian filter algorithm: ";
                                std::cin >> delta;
                                image2 = gaussianFilter(image2, delta);
                                break;
                            }
                            default:
                            {
                                std::cout << "Please enter only valid options" << std::endl;
                                break;
                            }
                        }
                        break;
                    }
                    case 4:
                    {
                        // user about to further process image so set undo
                        // image to current processed image
                        image3 = image2;
                        std::cout << "Please enter what value you would like to edit:" << std::endl;
                        std::cout << "1. Brightness" << std::endl;
                        std::cout << "2. Saturation" << std::endl;
                        // get user value editting option and do corresponding
                        // value edit
                        int option2;
                        std::cin >> option2;
                        switch (option2) {
                            case 1:
                            {
                                // get user contrast multiplier
                                double contrast;
                                while (true) {
                                    std::cout << "Please enter a contrast multiplier (1.0 to 3.0): ";
                                    std::cin >> contrast;
                                    if (contrast >= 1 && contrast <= 3) {
                                        break;
                                    } else {
                                        std::cout << "Please enter only valid values" << std::endl;
                                    }
                                }
                                // get user brightness adder
                                double brightness;
                                while (true) {
                                    std::cout << "Please enter a brightness adder (0.0 to 100.0): ";
                                    std::cin >> brightness;
                                    if (brightness >= 0 && brightness <= 100) {
                                        break;
                                    } else {
                                        std::cout << "Please enter only valid values" << std::endl;
                                    }
                                }
                                changeBrightness(image2, contrast, brightness);
                                break;
                            }
                            case 2:
                            {
                                // get user saturation multiplier
                                double satScale;
                                while (true) {
                                    std::cout << "Please enter a saturation multiplier (1.0 to 3.0): ";
                                    std::cin >> satScale;
                                    if (satScale >= 1 && satScale <= 3) {
                                        break;
                                    } else {
                                        std::cout << "Please enter only valid values" << std::endl;
                                    }
                                }
                                changeSaturation(image2, satScale);
                                break;
                            }
                            default:
                            {
                                std::cout << "Please enter only valid options" << std::endl;
                                break;
                            }
                        }
                        break;
                    }
                    case 5:
                    {
                        // user about to further process image so set undo
                        // image to current processed image
                        image3 = image2;
                        std::cout << "Please enter what type of Colorspace you would like:" << std::endl;
                        std::cout << "1. to Grayscale" << std::endl;
                        // get user colorspace option and apply corresponding
                        // conversion
                        int option2;
                        std::cin >> option2;
                        switch (option2) {
                            case 1:
                            {
                                image2 = toGrayscale(image2);
                                break;
                            }
                            default:
                            {
                                std::cout << "Please enter only valid options" << std::endl;
                                break;
                            }
                        }
                        break;
                    }
                    case 6: //FFT + inverse FFT
                    {
                        image3 = image2;
                        fourierRepresentation(image2);
                        break;
                    }

                    case 7:
                    {
                        // if images in same color space append editted image
                        // to original image, otherwise just display
                        // editted image (this is done because CImg will not
                        // display different colorspace simultaneously)
                        if (image.spectrum() == image2.spectrum()) {
                            image4.append(image2,'x');
                            image4.display("Original + Edited");
                            image4 = image;
                        } else {
                            image2.display("Edited");
                        }
                    }
                    case 8:
                    {
                        // set editted image to undo image
                        image2 = image3;
                        break;
                    }
                    case 9:
                    {
                        // this will stop while loop and allow user to exit
                        flag = false;
                        break;
                    }
                    default:
                    {
                        std::cout << "Please enter only valid options" << std::endl;
                        break;
                    }

                }
            }
            // if images in same color space append editted image to original
            // image, otherwise just display original image followed by
            // editted image (this is done because CImg will not display
            // different colorspace simultaneously)
            if (image.spectrum() == image2.spectrum()) {
                image.append(image2,'x');
                image.display("Original + Edited");
            } else {
                image.display("Original");
                image2.display("Edited");
            }
            // exit program
            return 0;
        } catch(std::exception& e) {
            std::cout << "Please input a valid filename" << std::endl;
        }
    }
    return 0;
}
