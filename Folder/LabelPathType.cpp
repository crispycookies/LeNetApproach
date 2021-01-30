//
// Created by tobi on 30.01.21.
//

#include "LabelPathType.h"

std::filesystem::path &LabelPathType::getPath() {
    auto & [a, b]  = mTuple;
    return a;
}

std::string &LabelPathType::getLabel() {
    auto & [a, b]  = mTuple;
    return b;
}

