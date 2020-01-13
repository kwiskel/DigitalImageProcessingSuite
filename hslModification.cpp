////////////////////////////////////////////////
// Name: Kyle Wiskel & Nayan Prakash
// ID #: 1540485 & 1533064
// CMPUT 275, Winter 2019
//
// CMPUT 275 Final Project -- Digital Image Processing Suite
////////////////////////////////////////////////

#include "CImg/CImg.h"
#include "hslModification.h"

using namespace cimg_library;

void changeSaturation(CImg<unsigned char> & image, double satScale) {

    /* Modifies the saturation of an image. First changes RGB to HSL then performs modifications.


    Arguments:
        CImg<unsigned char> image: The image
        double satScale: The saturation scale value (between 1.0 and 3.0)


    Return:
        None.
    */

    unsigned char oldPixel[3]; // old colours
    unsigned char hsl[3]; //intermediate values
    unsigned char newPixel[3]; // new colours
    for (int i  = 0; i < image.width(); i++) {
        for (int j = 0; j < image.height(); j++) {
            //std::cout << j << std::endl;
            oldPixel[0] = image(i,j,0,0); //red
            oldPixel[1] = image(i,j,0,1); //green
            oldPixel[2] = image(i,j,0,2); //blue
            // convert to HSL
            RGB2HSL(oldPixel[0], oldPixel[1], oldPixel[2], hsl[0], hsl[1], hsl[2]);
            // check if image has at least some saturation
            // better would be to find max current sat
            if (hsl[1] >= 10) {
                // increase saturation by factor up to 100%
                hsl[1] = (unsigned char)(((double)hsl[1]*satScale));
                if (hsl[1] > 100) {
                    // constrain between 0 and 100
                    hsl[1] = 100;
                }
                //convert back to RGB
                HSL2RGB(hsl[0],hsl[1],hsl[2],newPixel[0],newPixel[1],newPixel[2]);
                // change pixel values
                image(i,j,0,0) = newPixel[0];
                image(i,j,0,1) = newPixel[1];
                image(i,j,0,2) = newPixel[2];
            }
        }
    }

}

void changeBrightness(CImg<unsigned char> & image, double contrast, double brightness) {


    /* Modifes the brightness and constrast of an image. First changes RGB to HSL then performs modifications.


    Arguments:
        CImg<unsigned char> image: The image
        double contrast: The contrast scale value (between 1.0 and 3.0)
        double brightness: THe brightness increase value

    Return:



    */

    // changes the brightness of the image by a scaling factor 'scale'
    unsigned char oldPixel[3]; // old colours
    unsigned char hsl[3]; //intermediate values
    unsigned char newPixel[3]; // new colours
    for (int i  = 0; i < image.width(); i++) {
        for (int j = 0; j < image.height(); j++) {
            oldPixel[0] = image(i,j,0,0); //red
            oldPixel[1] = image(i,j,0,1); //green
            oldPixel[2] = image(i,j,0,2); //blue
            // convert to HSL
            if (oldPixel[0] < 5 && oldPixel[1] < 5 && oldPixel[2] < 5) {
                // almost black  -- hard to contrast or increase brightness --> estimate as pure blacl
                oldPixel[0] = 0;
                oldPixel[1] = 0;
                oldPixel[2] = 0;
            }
            RGB2HSL(oldPixel[0], oldPixel[1], oldPixel[2], hsl[0], hsl[1], hsl[2]);
            // increase lightness by factor up to 100%

            hsl[2] = (unsigned char)(((double)hsl[2]*contrast)+ brightness);
            if (hsl[2] > 100) {
                // constrain between 0 and 100
                hsl[2] = 100;
            }
            //convert back to RGB
            HSL2RGB(hsl[0],hsl[1],hsl[2],newPixel[0],newPixel[1],newPixel[2]);
            // change pixel values
            image(i,j,0,0) = newPixel[0];
            image(i,j,0,1) = newPixel[1];
            image(i,j,0,2) = newPixel[2];
        }
    }
}

void RGB2HSL(unsigned char r, unsigned char g, unsigned char b, unsigned char& h, unsigned char& s, unsigned char& l) {

    /* Converts an RGB value to HSL


    Arguments:
        unsigned char r: The red value
        unsigned char g: The green value
        unsigned char b: The blue value
        unsigned char&h: pointer to store the h value
        unsigned char&s: pointer to store the s value
        unsigned char&l: pointer to store the l value

    Return:



    */

    // first convert RGB to range 0-1 --. 8 bit color depth
    double red = ((double)r)/255;
    double green = ((double)g)/255;
    double blue = ((double)b)/255;



    double maxC = 0;
    double minC = 0;

    // find max
    if (red >= green && red >= blue) {
        maxC = red;
    } else if (green >= red && green >= blue) {
        maxC = green;
    } else {
        maxC = blue;
    }
    // find min
    if (red <= green && red <= blue) {
        minC = red;
    } else if (green <= red && green <= blue) {
        minC = green;
    } else {
        minC = blue;
    }

    // find the brightness value
    l = floor(((maxC+minC)/2)*100);
    //l = ceil((maxC + minC)/2) *100;

    // if max and min are same --> no saturation + no hue
    if(maxC != minC) {
        // check luminance level to calculate saturation
        if ((((double)l)/100) < 0.5) {
            s = floor(((maxC-minC)/(maxC+minC)) *100);
        } else {
            s = floor(((maxC-minC)/(2-maxC-minC)) *100);
        }

        // calculate hue
        if (red == maxC) {
            h = floor(((green-blue)/(maxC-minC))*60);
        }else if(green == maxC) {
            h = floor((2+((blue-red)/(maxC-minC))) * 60);
        }else { // blue is max
            h = floor((4+((red-green)/(maxC-minC))) * 60);
        }
        if (h < 0) {
            h += 360;
        }

    } else {
        // no saturation or hue
        s = 0;
        h = 0;
    }

    // s and l in percentages
    // h in degrees



}

void HSL2RGB(unsigned char h, unsigned char s, unsigned char l, unsigned char& r, unsigned char& g, unsigned char& b) {

     /* Converts an HSL to RGB value according to the algorithm at the link below (formulas)


    Arguments:
        unsigned char h: The hue value
        unsigned char s: The saturation value
        unsigned char l: The brightness value
        unsigned char&r: pointer to store the r value
        unsigned char&g: pointer to store the g value
        unsigned char&b: pointer to store the b value

    Return:
        None.
    */


    //http://www.niwa.nu/2013/05/math-behind-colorspace-conversions-rgb-hsl/
    // if s and l in percentages (0 to 100) and h in degrees (0 to 360)


    double hue = ((double)h)/360;
    double sat = ((double)s)/100;
    double light = ((double)l)/100;
    double temp1;
    double temp2;
    double tempR;
    double tempG;
    double tempB;



    if (h == 0 && s == 0) {
        r = round((light)*255);
        g = r;
        b = r;
    } else {
        // not just shade of grey --> convert
        if (light < 0.5) {
            temp1 = light*(1+sat);
        } else {
            temp1 = light + sat - light*sat;
        }
        temp2 = 2*light-temp1;
        tempR = hue + 0.333;
        tempG = hue;
        tempB = hue -0.333;
        if (tempR >1) {
            tempR -=1;
        } else if (tempR < 0) {
            tempR +=1;
        }
        if (tempG >1) {
            tempG -=1;
        } else if (tempG < 0) {
            tempG +=1;
        }
        if (tempB >1) {
            tempB -=1;
        } else if (tempB < 0) {
            tempB +=1;
        }

        r = floor(colourTest(tempR,temp1,temp2)*255);
        g = floor(colourTest(tempG,temp1,temp2)*255);
        b = floor(colourTest(tempB,temp1,temp2)*255);
        // 3 tests for each colour channel to select correct value

    }

}

double colourTest(double tempC, double temp1, double temp2) {

    /* Performs a simple test on some temporary values to assist with conversion from RGB to HSL


    Arguments:
        double tempC: temporary value of colour (either r,g, or b)
        double temp1: first temporary value
        double temp2: second temporary value

    Return:
        double: The new value of the colour (either r,g, or b)

    */

    // performs test for colour to select correct value when converting HSL to RGB
    double colour =  0;
    if (6*tempC < 1) {
        // test 1
        colour = temp2 + (temp1-temp2)*6*tempC;
    } else {
        if (2 * tempC < 1) {
            // test 2
            colour = temp1;
        } else {
            if (3* tempC < 2) {
                // third test
                colour = temp2 + (temp1-temp2)*(0.666-tempC)*6;
            } else {
                colour = temp2;
            }
        }
    }
    return colour;
}
