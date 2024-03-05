#include "ImageMatrix.h"
#include <iostream>


// Default constructor
ImageMatrix::ImageMatrix() : height(0), width(0), data(nullptr){

}


// Parameterized constructor for creating a blank image of given size
ImageMatrix::ImageMatrix(int imgHeight, int imgWidth) : height(imgHeight), width(imgWidth) {

    // Allocate memory for the matrix and fill it with zeros to create blank image
    data = new double * [height];
    for (int i = 0; i < height; ++i) {
        data[i] = new double[width];
        for (int j = 0; j < width; ++j) {
            data[i][j] = 0.0;
        }
    }

}

// Parameterized constructor for loading image from file. PROVIDED FOR YOUR CONVENIENCE
ImageMatrix::ImageMatrix(const std::string &filepath) {
    // Create an ImageLoader object and load the image
    ImageLoader imageLoader(filepath);

    // Get the dimensions of the loaded image
    height = imageLoader.getHeight();
    width = imageLoader.getWidth();

    // Allocate memory for the matrix
    data = new double*[height];
    for (int i = 0; i < height; ++i) {
        data[i] = new double[width];
    }

    // Copy data from imageLoader to data
    double** imageData = imageLoader.getImageData();
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            data[i][j] = imageData[i][j];
        }
    }
}



// Destructor
ImageMatrix::~ImageMatrix() {
    if(data != nullptr) {
        for (int i = 0; i < height; ++i) {
            delete[] data[i];
        }
        delete[] data;
    }
}

// Parameterized constructor - direct initialization with 2D matrix
ImageMatrix::ImageMatrix(const double** inputMatrix, int imgHeight, int imgWidth): height(imgHeight), width(imgWidth){

    // Allocate memory for the matrix and fill it with given inputMatrix
    data = new double * [height];
    for (int i = 0; i < height; ++i) {
        data[i] = new double[width];
        for (int j = 0; j < width; ++j) {
            data[i][j] = inputMatrix[i][j];
        }
    }
}

// Copy constructor
ImageMatrix::ImageMatrix(const ImageMatrix &other) : height(other.height), width(other.width) {
    // Allocate memory for the matrix and copy data
    data = new double * [height];

    for (int i = 0; i < height; ++i) {
        data[i] = new double[width];

        for (int j = 0; j < width; ++j){
            data[i][j] = other.data[i][j];
        }
    }
}

// Copy assignment operator
ImageMatrix& ImageMatrix::operator=(const ImageMatrix &other) {

    // Check whether they are already same
    if (this == &other) {
        return *this;
    }

    if (data != nullptr){
        for (int i = 0; i < height; ++i){
            delete [] data[i];
        }
        delete [] data;
    }

    // Assign new value of variables
    height = other.height;
    width = other.width;
    data = new double * [height];
    for (int i = 0; i < height; ++i) {
        data[i] = new double[width];
        for (int j = 0; j < width; ++j) {
            data[i][j] = other.data[i][j];
        }
    }

    return *this;
}



// Overloaded operators

// Overloaded operator + to add two matrices
ImageMatrix ImageMatrix::operator+(const ImageMatrix &other) const {

    // Create ImageMatrix with using parameterized constructor for creating a blank image to return result image
    ImageMatrix result(height, width);
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            double value = data[i][j] + other.data[i][j];

            // In sharpen method the result might go over the limit. To prevent this, result is limited.
            result.data[i][j] = (value > 255.0 ? 255.0: (value < 0.0 ? 0.0 : value));
        }
    }
    return result;



}

// Overloaded operator - to subtract two matrices
ImageMatrix ImageMatrix::operator-(const ImageMatrix &other) const {
    // Create ImageMatrix with using parameterized constructor for creating a blank image to return result image
    ImageMatrix result(height, width);
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            result.data[i][j] = data[i][j] - other.data[i][j];
        }
    }
    return result;
}

// Overloaded operator * to multiply a matrix with a scalar
ImageMatrix ImageMatrix::operator*(const double &scalar) const {
    // Create ImageMatrix with using parameterized constructor for creating a blank image to return result image
    ImageMatrix result(height, width);
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            result.data[i][j] = data[i][j] * scalar;
        }
    }
    return result;
}


// Getter function to access the data in the matrix
double** ImageMatrix::get_data() const {
    return data;
}

// Getter function to access the data at the index (i, j)
double ImageMatrix::get_data(int i, int j) const {
    if(i < height && j < width) {
        return data[i][j];
    }
    return -1;
}

// Getter function to access the height
int ImageMatrix::get_height() const {
    return height;
}

// Getter function to access the width
int ImageMatrix::get_width() const {
    return width;
}

// Setter function to change data[i][j] by reference
void ImageMatrix::setData(double value, int i, int j) {
    double &data_ref = data[i][j];
    data_ref = value;
}

