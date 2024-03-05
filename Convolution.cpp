#include <iostream>

#include "Convolution.h"

// Default constructor 
Convolution::Convolution(): kernel(nullptr), kh(3), kw(3), stride_val(1), pad(true) {

}

// Parametrized constructor for custom kernel and other parameters
Convolution::Convolution(double** customKernel, int kh, int kw, int stride_val, bool pad)
    : kh(kh), kw(kw), stride_val(stride_val), pad(pad) {

    // Allocate memory for the kernel and fill it with given customKernel
    kernel = new double * [kh];
    for (int i = 0; i < kh; ++i) {
        kernel[i] = new double[kw];

        for (int j = 0; j < kw; ++j) {
            kernel[i][j] = customKernel[i][j];
        }
    }
}

// Destructor
Convolution::~Convolution() {
    if(kernel != nullptr) {
        for (int i = 0; i < kh; ++i) {
            delete [] kernel[i];
        }
        delete [] kernel;
    }
}

// Copy constructor
Convolution::Convolution(const Convolution &other)
    : kh(other.kh), kw(other.kw), stride_val(other.stride_val), pad(other.pad){

    // Allocate memory for the kernel and copy
    kernel = new double * [kh];
    for (int i = 0; i < kh; ++i) {
        kernel[i] = new double[kw];

        for (int j = 0; j < kw; ++j) {
            kernel[i][j] = other.kernel[i][j];
        }
    }
}

// Copy assignment operator
Convolution& Convolution::operator=(const Convolution &other) {

    // Check whether they are already same
    if(this == &other) {
        return *this;
    }

    if (kernel != nullptr) {
        for (int i = 0; i < kh; ++i) {
            delete[] kernel[i];
        }
        delete[] kernel;
    }

    // Assign new value of variables
    kh = other.kh;
    kw = other.kw;
    stride_val = other.stride_val;
    pad = other.pad;
    kernel = new double * [kh];
    for (int i = 0; i < kh; ++i) {
        kernel[i] = new double[kw];
        for (int j = 0; j < kw; ++j) {
            kernel[i][j] = other.kernel[i][j];
        }
    }
    return *this;
}


// Convolve Function: Responsible for convolving the input image with a kernel and return the convolved image.
ImageMatrix Convolution::convolve(const ImageMatrix& input_image) const {
    // Getting input height and width of input_image
    int input_height = input_image.get_height() + (pad ? 2 : 0);
    int input_width = input_image.get_width() + (pad ? 2 : 0);

    // Calculating the height and width of convolved matrix
    int output_height = ((input_height - kh) / stride_val) + 1;
    int output_width = ((input_width - kw) / stride_val) + 1;

    // With using height and width creating blank image
    ImageMatrix convolvedImage(output_height, output_width);

    //Padding data with zeros
    double paddedData[input_height][input_height];
    if (pad){
        for (int i = 0; i < input_height; ++i) {
            for (int j = 0; j < input_width; ++j) {
                if (i == 0 || j == 0 || (i == input_height - 1) || (j == input_width - 1)) {
                    paddedData[i][j] = 0;
                }
                else {
                    paddedData[i][j] = input_image.get_data(i - 1, j - 1);
                }
            }
        }
    }
    // out_h and out_w are for output_image, m and for input_image data, i and j for kernel to loop.
    int out_h = 0;
    // Looping input_image
    for (int m = 0; m <= input_height - kh; m += stride_val) {
        int out_w = 0;
        for (int n = 0; n <= input_width - kw; n += stride_val) {
            double sum = 0; // IxK
            // Looping kernel
            for (int i = 0; i < kh; ++i) {
                for (int j = 0; j < kw; ++j) {
                    if (pad)
                        sum += paddedData[m + i][n + j] * kernel[i][j];
                    else
                        sum+= input_image.get_data(m + i, n + j) * kernel[i][j];
                }
            }
            convolvedImage.setData(sum, out_h, out_w);
            ++out_w;
        }
        ++out_h;
    }

    return convolvedImage;
}
