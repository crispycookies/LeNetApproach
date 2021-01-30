//
// Created by tobi on 30.01.21.
//

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
