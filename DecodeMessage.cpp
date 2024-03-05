// DecodeMessage.cpp

#include "DecodeMessage.h"
#include <iostream>
#include <cmath>

// Default constructor
DecodeMessage::DecodeMessage() {
    // Nothing specific to initialize here
}

// Destructor
DecodeMessage::~DecodeMessage() {
    // Nothing specific to clean up
}


std::string DecodeMessage::decodeFromImage(const ImageMatrix& image, const std::vector<std::pair<int, int>>& edgePixels) {

    // Get lsb of edges and store them in lsb string
    std::string lsb;
    int length = edgePixels.size();
    for (int i = 0; i < length; ++i) {
        int val =(int) image.get_data(edgePixels[i].first, edgePixels[i].second);
        lsb += std::to_string(val & 1);
    }

    // Padding
    while (lsb.size() % 7 != 0) {
        lsb = "0" + lsb;
    }

    // Get decimal values of 7 bits and transform it to char
    std::string decodedMessage;
    for(int i = 0; i < lsb.size(); i+=7){
        int decimal_value = 0;
        for(int j = 0; j < 7; ++j){
            if(lsb[i+j] == '1') {
                decimal_value += (int) pow(2,(6-j));
            }
        }
        decimal_value = (decimal_value < 33 ? 33 + decimal_value: (decimal_value > 126 ? 126: decimal_value));
        decodedMessage+= static_cast<char>(decimal_value);
    }
    return decodedMessage;
}

