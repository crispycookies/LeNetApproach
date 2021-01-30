/**
 * @file DummyProcessor.cpp
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
