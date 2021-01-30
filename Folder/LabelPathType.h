//
// Created by tobi on 30.01.21.
//

#ifndef LENET_LABELPATHTYPE_H
#define LENET_LABELPATHTYPE_H

#include <filesystem>
#include <tuple>

#include "../Object.h"

class LabelPathType : public Object{
protected:
    std::tuple<std::filesystem::path, std::string> mTuple;
public:
    LabelPathType(const std::filesystem::path & path, const std::string & label) : mTuple(path, label) {};

    virtual std::filesystem::path & getPath();
    virtual std::string & getLabel();

    ~LabelPathType() override = 0;
};

#endif //LENET_LABELPATHTYPE_H
