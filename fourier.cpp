////////////////////////////////////////////////
// Name: Kyle Wiskel & Nayan Prakash
// ID #: 1540485 & 153306
// CMPUT 275, Winter 2019
//
// CMPUT 275 Final Project -- Digital Image Processing Suite
////////////////////////////////////////////////

#include "CImg/CImg.h"
#include <complex>
#include <vector>
#include <iostream>
#include "fourier.h"

using namespace cimg_library;



std::vector<std::complex<double>> fastFourierTransform(std::vector<std::complex<double>>& values) {

    /* Performs the FFT algorithm on a vector of complex numbers. This is the Cooley-Tukey for of FFT
    and therefore can only be implemented with images with a size that is a multiple of 2.


    Arguments:
        std::vector<std::complex<double>>& values: Vector containing complex pairs of values
            --> These complex pairs are either the original image values (real part only) or the values
            after a single FT (when performing inverse FFT to convert back to original values (space domain))


    Return:
        std::vector<std::complex<double>>: Returns the vector values after the FFT has been performed

    */


    // size N must be a power of 2
    int n = values.size();
    if (n == 1) { // reduced down to size 1
        return values;
    } else {
        int m = n/2;
        // create even and odd then combine
        // create even with size n/2
        std::vector<std::complex<double>> even(m);
        // create odd with size n/2
        std::vector<std::complex<double>> odd(m);

        for (int  i = 0; i < m; i++) {
            even[i] = values[2*i];
            odd[i] = values[2*i+1];
        }

        // perform FFT recursively
        std::vector<std::complex<double>> fourierEven(m);
        std::vector<std::complex<double>> fourierOdd(m);
        fourierEven = fastFourierTransform(even);
        fourierOdd = fastFourierTransform(odd);

        //combine even and add to create full complex representation
        std::vector<std::complex<double>> fourier(n);

        for (int i = 0; i < m ;i++) {
            std::complex<double> cExp = std::polar(1.0, -2*atan(1)*4*(i/n))*fourierOdd[i];
            fourier[i] = fourierEven[i] + cExp;

            fourier[i+n/2] = fourierEven[i] - cExp;
        }
        return fourier;
    }
}

void slowFourierTransform(CImg<unsigned char> image) {

    /* This function performs the slowFourierTransform on an image. The speed of the algorithm is O(n^2)
    which is significantly slower than the FFT

    Arguments:
        CImg<unsigned char> image: The image file

    Return:
            ./

    */

    // array to store real and complex representations
    // size of Fourier representation == size of image
    int x = image.width();
    int y = image.height();
    int size = 2; // real and imaginary parts
    int k = image.spectrum();
    float Fourier[x][y][2*k]; // x*y array with complex values --> for image with any spectrum
    float real;
    float imaginary;
    std::complex<double> fComplex (0,0);
    // 2d fourier transform

    for (int i = 0; i < 1; i ++) {
        for (int j = 0; j < 1; j++) {
            // sum for each value in frequency domain
            for (int a = 0; a < k; a++) { // loop through for every spectrum
                fComplex = std::polar(0,0);
                real = 0;
                imaginary = 0;
                for (int m = 0; m < x; m++) { // loop through width
                    for (int n = 0; n < y; n++) { // loop through height
                        real += (double)image(m,n,0,a)*cos(-2*atan(1)*4*(((i*m)/x)+((j*n)/y)));
                        imaginary += (double)image(m,n,0,a)*sin(-2*atan(1)*4*(((i*m)/x)+((j*n)/y)));
                        // complex number with magnitude and phase angle
                    }
                }
                Fourier[i][j][2*a] = real;
                Fourier[i][j][2*a+1] = imaginary;
                std::cout << real << " " << imaginary << std::endl;
            }

        }
    }
    // 1D fourier transform performed twice
    // first compute horizontal then vertical

}

void fourierRepresentation(CImg<unsigned char> image) {

    /* Performs the FFT on a spectrum of the image and the performs the inverse FFT.
    The inverse is stored in image3, and the FFT of the spectrum is stored in image2.



    Arguments:
        CImg<unsigned char> image --> The image
    Return:


    */

    CImg<unsigned char> image2 = image;
    CImg<unsigned char> image3 = image;
    if (image.width()%2 == 0 && image.height()%2 == 0){
        // compute FFT
        int index1 = 0;
        int index2 = 0;
        for (int k = 0; k < 1; k++) {
            std::vector<std::complex<double>> vImage1(image.width()*image.height());
            for (int i = 0; i < image.width();i++) {
                for (int j =0; j < image.height(); j++) {
                    vImage1.push_back(std::polar((double)image(i,j,0,k),0.0));
                }
            }

            std::vector<std::complex<double>> f1 = fastFourierTransform(vImage1);
            std::vector<std::complex<double>> f2 = f1;
            index1=0;
            index2=0;
            // image 3 --> FFT then inverse FFT
            f2 = fastFourierTransform(f2);
            for (std::complex<double> n:f2) {
                image3(index1,index2,0,k) = (unsigned char)(std::real(n/((double)image.width()*image.height()*2)));
                index2++;
                if (index2 == image.height()) {
                    index2 = 0;
                    index1++;
                }
            }
        }
    }
    image.append(image3,'x');
    image.display("Comparison");
}
