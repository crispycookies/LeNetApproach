//
// Created by tobi on 30.01.21.
//

#include "LabelDataType.h"

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>

void LabelDataType::load() {
    auto & [a,b,c] = mTuple;
    if(!std::filesystem::exists(b)){
        throw std::invalid_argument("File does not Exist / In Line: " + std::to_string(__LINE__) + " of File: " + __FILE__);
    }
    mData = cv::imread(b.string(), cv::IMREAD_COLOR);
}

void LabelDataType::doProcess(const std::shared_ptr<IProcessor> &processor) {
    if(processor == nullptr){
        throw std::invalid_argument("Nullptr in Line: " + std::to_string(__LINE__) + " of File: " + __FILE__);
    }
    if(mData.empty()){
        throw std::logic_error("mData Empty in Line: " + std::to_string(__LINE__) + " of File: " + __FILE__);
    }
    processor->setData(mData);
    processor->process();
    mData = processor->getData();
}

std::string &LabelDataType::getLabel() {
    auto & [a , b, c] = mTuple;
    return a;
}

std::filesystem::path &LabelDataType::getPath() {
    auto & [a , b, c] = mTuple;
    return b;
}

std::string &LabelDataType::getName() {
    auto & [a , b, c] = mTuple;
    return c;
}

cv::Mat &LabelDataType::getData() {
    return mData;
}
