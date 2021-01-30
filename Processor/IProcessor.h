//
// Created by tobi on 30.01.21.
//

#ifndef LENET_IPROCESSOR_H
#define LENET_IPROCESSOR_H

#include "../Object.h"
#include <opencv2/core/mat.hpp>

class IProcessor : public Object{
protected:
    IProcessor() = default;
public:
    ~IProcessor() override = default;
    virtual void setData(const cv::Mat & data) = 0;
    virtual void process() = 0;
    virtual cv::Mat getData() = 0;
};

#endif //LENET_IPROCESSOR_H
