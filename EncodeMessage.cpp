#include "EncodeMessage.h"
#include <iostream>


// Default Constructor
EncodeMessage::EncodeMessage() {

}

// Destructor
EncodeMessage::~EncodeMessage() {

}

// Function to encode a message into an image matrix
ImageMatrix EncodeMessage::encodeMessageToImage(const ImageMatrix &img, const std::string &message, const std::vector<std::pair<int, int>>& positions) {
    int length = (int) message.length();
    ImageMatrix encodedImage(img);
    std::string manipulated_message = message;
    for (int i = 0; i < length; ++i) {
        if(is_prime_number(i)) {
            int decimal_value = static_cast<int>(message[i]);
            decimal_value += fibonacci_num(i);
            decimal_value = (decimal_value < 33 ? (decimal_value + 33) : (decimal_value > 126 ? 126 : decimal_value));
            manipulated_message[i] += (char)decimal_value;
        }
    }
    int shift_num = length / 2;
    std::string shifted_message;
    for(int i = 0; i < shift_num; ++i){
        shifted_message += manipulated_message[length - i -1];
    }
    for(int i = 0; i < length - shift_num; ++i){
        shifted_message += manipulated_message[i];
    }
    std::string binary_string;
    for (int i = 0; i < length; ++i) {
        binary_string += decimal_to_binary(static_cast<int>(message[i]));
    }
    for (int i = 0; i < positions.size(); ++i) {
        int x = positions[i].first;
        int y = positions[i].second;
        int value = (int) encodedImage.get_data(x, y);
        if (binary_string[i] == '1') {
            encodedImage.setData((value |= 1), x, y);
        }
        if (binary_string[i] == '0') {
            encodedImage.setData((value & ~0), x, y);
        }
    }

    return encodedImage;
}

bool EncodeMessage::is_prime_number(int n) {
    if(n < 2){
        return false;
    }
    for (int i = 2; i <= n / 2; ++i){
        if(n % i == 0) {
            return false;
            break;
        }
    }
    return true;
}

//This is a recursive function to corresponding nth number. But it doesn't return fibonacci number of negative values.
int EncodeMessage::fibonacci_num(int n) {
    if(n <= 0 || n == 1) return n;
    return fibonacci_num(n - 1) + fibonacci_num(n-2);
}

std::string EncodeMessage::decimal_to_binary(int n) {
    std::string binary_string;
    if (n == 0) return "0";
    while (n > 0) {
        int remainder = n % 2;
        binary_string = std::to_string(remainder) + binary_string;
        n /= 2;
    }
    return binary_string;
}
