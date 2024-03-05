#include "ImageProcessor.h"

ImageProcessor::ImageProcessor() {

}

ImageProcessor::~ImageProcessor() {

}


std::string ImageProcessor::decodeHiddenMessage(const ImageMatrix &img) {
    ImageSharpening sharpening;
    ImageMatrix sharpenImage(sharpening.sharpen(img, 2));
    EdgeDetector edgeDetector;
    DecodeMessage decodeMessage;
    return (decodeMessage.decodeFromImage(sharpenImage, edgeDetector.detectEdges(sharpenImage)));

}

ImageMatrix ImageProcessor::encodeHiddenMessage(const ImageMatrix &img, const std::string &message) {
    ImageMatrix decodedImage(img);
    ImageProcessor::decodeHiddenMessage(decodedImage);
    ImageMatrix encodedImage(img);
    EdgeDetector edgeDetector;
    EncodeMessage encode;
    return encode.encodeMessageToImage(encodedImage, message, edgeDetector.detectEdges(img));
}
