// EdgeDetector.cpp

#include "EdgeDetector.h"
#include <cmath>

#include "EdgeDetector.h"
#include <cmath>

// Default constructor
EdgeDetector::EdgeDetector() {
    // Creating 2D dynamic arrays for Gx and Gy kernels
    gx_kernel = new double * [3];
    gx_kernel[0] = new double[3]{-1.0, 0.0, 1.0};
    gx_kernel[1] = new double[3]{-2.0, 0.0, 2.0};
    gx_kernel[2]  = new double[3]{-1.0, 0.0, 1.0};
    gy_kernel = new double * [3];
    gy_kernel[0] = new double[3]{-1.0, -2.0, -1.0};
    gy_kernel[1] = new double[3]{0.0, 0.0, 0.0};
    gy_kernel[2]  = new double[3]{1.0, 2.0, 1.0};

}

// Destructor
EdgeDetector::~EdgeDetector() {

}

// Detect Edges using the given algorithm
std::vector<std::pair<int, int>> EdgeDetector::detectEdges(const ImageMatrix& input_image) {

    // Define convolution objects of Gx and Gy
    Convolution gx_convolution(gx_kernel, 3, 3, 1, true);
    Convolution gy_convolution(gy_kernel, 3, 3, 1, true);

    // Create images Ix and Iy
    ImageMatrix i_x = gx_convolution.convolve(input_image);
    ImageMatrix i_y = gy_convolution.convolve(input_image);
    int height = i_x.get_height();
    int width = i_x.get_width();

    // To store result of formula define 2D array
    double magnitudes[height][width];
    double sum = 0;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            double magnitude = sqrt(pow(i_x.get_data(i, j), 2) + pow(i_y.get_data(i, j), 2));
            magnitudes[i][j] = magnitude;
            sum += magnitude;

        }

    }

    // Getting threshold and find edges
    double threshold = sum / (height * width);
    std::vector<std::pair<int, int>> threshold_pairs;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (magnitudes[i][j] > threshold) {
                threshold_pairs.push_back(std::make_pair(i, j));
            }
        }
    }
    return threshold_pairs;
}

