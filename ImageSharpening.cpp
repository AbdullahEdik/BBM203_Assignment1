#include "ImageSharpening.h"

// Default constructor
ImageSharpening::ImageSharpening(): kernel_height(3), kernel_width(3) {
    // Creating 2D dynamic array for blurring_kernel
    blurring_kernel = new double * [kernel_height];
    for (int i = 0; i < kernel_height; ++i) {
        blurring_kernel[i] = new double[kernel_width];
        for (int j = 0; j < kernel_width; ++j) {
            blurring_kernel[i][j] = 1.0/9.0;
        }

    }
}

ImageSharpening::~ImageSharpening(){
    if(blurring_kernel != nullptr) {
        for (int i = 0; i < kernel_height; ++i) {
            delete[] blurring_kernel[i];
        }
        delete[] blurring_kernel;
    }
}

ImageMatrix ImageSharpening::sharpen(const ImageMatrix& input_image, double k) {
    ImageMatrix blurred_image;
    Convolution convolution(blurring_kernel, kernel_height, kernel_width, 1, true);
    blurred_image = convolution.convolve(input_image);
    return input_image + ((input_image - blurred_image) * k);
}
