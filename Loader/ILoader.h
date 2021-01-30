//
// Created by tobi on 30.01.21.
//

#ifndef LENET_ILOADER_H
#define LENET_ILOADER_H

#include "../Object.h"
#include "../File/LabelDataType.h"
#include "../Folder/LabelPathType.h"

class [[maybe_unused]] ILoader : private Object {
protected:
    ILoader() = default;
public:
    ~ILoader() override = default;

    [[maybe_unused]] typedef LabelDataType lw_label_data_t;
    [[maybe_unused]] typedef LabelPathType lw_label_path_t;
    typedef std::shared_ptr<lw_label_path_t> lw_label_path_ptr_t;
    typedef std::shared_ptr<lw_label_data_t> lw_label_data_ptr_t;

    typedef std::vector<lw_label_path_ptr_t> lw_label_path_ptr_vect_t;
    typedef std::vector<lw_label_data_ptr_t> lw_label_data_ptr_vect_t;


    [[maybe_unused]] virtual void setPathsWithLabels(const lw_label_path_ptr_vect_t & paths_with_label) = 0;
    [[maybe_unused]] virtual void load() = 0;
    [[maybe_unused]] virtual void commit() = 0;
    [[maybe_unused]] virtual void process(const std::shared_ptr<IProcessor> & processor) = 0;
    [[maybe_unused]] virtual lw_label_data_ptr_vect_t getData() = 0;
};

#endif //LENET_ILOADER_H
