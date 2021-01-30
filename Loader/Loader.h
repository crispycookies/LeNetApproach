//
// Created by tobi on 30.01.21.
//

#ifndef LENET_LOADER_H
#define LENET_LOADER_H

#include "ILoader.h"

class Loader : public ILoader{
protected:
    lw_label_path_ptr_vect_t mPaths;
    lw_label_data_ptr_vect_t mData;

    virtual void getDirectoryContent(const lw_label_path_ptr_t & t);
public:
    Loader() = default;

    [[maybe_unused]] void setPathsWithLabels(const lw_label_path_ptr_vect_t & paths_with_label) override;
    [[maybe_unused]] void load() override;
    [[maybe_unused]] void commit() override;
    [[maybe_unused]] void process(const std::shared_ptr<IProcessor> & processor) override;
    [[maybe_unused]] lw_label_data_ptr_vect_t getData() override;


};


#endif //LENET_LOADER_H
