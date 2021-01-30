//
// Created by tobi on 30.01.21.
//

#ifndef LENET_DUMMYPROCESSOR_H
#define LENET_DUMMYPROCESSOR_H

#include "IProcessor.h"

class DummyProcessor : public IProcessor {
protected:
    cv::Mat mData;
public:
    ~DummyProcessor() override = default;

    void setData(const cv::Mat &data) override;

    void process() override;

    cv::Mat getData() override;
};


#endif //LENET_DUMMYPROCESSOR_H
