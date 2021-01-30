/**
 * @file LabelDataType.h
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

#ifndef LENET_LABELDATATYPE_H
#define LENET_LABELDATATYPE_H

#include "../Object.h"

#include <tuple>
#include <filesystem>
#include <string>
#include <opencv2/core/mat.hpp>

#include "../Processor/IProcessor.h"

class LabelDataType : public Object{
protected:
    std::tuple<std::string, std::filesystem::path, std::string> mTuple;
    cv::Mat mData;
public:
    LabelDataType(const std::string & label, const std::filesystem::path & path) : mTuple({label, path, path}) {}
    LabelDataType(const std::string & label, const std::filesystem::path & path, const std::string & name) : mTuple({label, path, name}) {}

    virtual void load();
    virtual void doProcess(const std::shared_ptr<IProcessor> & processor);

    virtual std::string & getLabel();
    virtual std::filesystem::path & getPath();
    virtual std::string & getName();

    virtual cv::Mat & getData();

    ~LabelDataType() = default;
};

#endif //LENET_LABELDATATYPE_H
