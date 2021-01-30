//
// Created by tobi on 30.01.21.
//

#include <iostream>
#include "DummyProcessor.h"

void DummyProcessor::setData(const cv::Mat &data) {
    if(data.empty()){
        throw std::logic_error("data Empty in Line: " + std::to_string(__LINE__) + " of File: " + __FILE__);
    }
    mData = data;
}

void DummyProcessor::process() {
    std::cout << "Processing Called" << std::endl;
}

cv::Mat DummyProcessor::getData() {
    return mData;
}
