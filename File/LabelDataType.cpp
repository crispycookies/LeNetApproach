/**
 * @file LabelDataType.cpp
 * @brief -
 * @author Tobias Egger, Daniel Giritzer
 * @copyright
 * MIT License

 * Copyright (c) 2021 Tobias Egger, Daniel Giritzer

 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

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
