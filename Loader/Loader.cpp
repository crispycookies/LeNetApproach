//
// Created by tobi on 30.01.21.
//

#include "Loader.h"

void Loader::setPathsWithLabels(const ILoader::lw_label_path_ptr_vect_t &paths_with_label) {
    if(paths_with_label.empty()){
        throw std::logic_error("Empty Path Vector in Line: " + std::to_string(__LINE__) + " of File: " + __FILE__);
    }
    for(auto & i : paths_with_label){
        mPaths.push_back(i);
    }
}

void Loader::load() {
    if(mPaths.empty()){
        throw std::logic_error("Empty Path Vector in Line: " + std::to_string(__LINE__) + " of File: " + __FILE__);
    }
    for(auto & i : mPaths) {
        getDirectoryContent(i);
    }
}

void Loader::commit() {
    if(mData.empty()){
        throw std::logic_error("Empty Data Vector in Line: " + std::to_string(__LINE__) + " of File: " + __FILE__);
    }
    for(auto & i : mData){
        if(i == nullptr){
            throw std::logic_error("Nullptr in Data Vector in Line: " + std::to_string(__LINE__) + " of File: " + __FILE__);
        }
        i->load();
    }
}

void Loader::process(const std::shared_ptr<IProcessor> &processor) {
    if(processor == nullptr){
        throw std::logic_error("Empty Processor in Line: " + std::to_string(__LINE__) + " of File: " + __FILE__);
    }
    if(mData.empty()){
        throw std::logic_error("Empty Data Vector in Line: " + std::to_string(__LINE__) + " of File: " + __FILE__);
    }
    for(auto & i : mData){
        if(i == nullptr){
            throw std::logic_error("Nullptr in Data Vector in Line: " + std::to_string(__LINE__) + " of File: " + __FILE__);
        }
        i->doProcess(processor);
    }
}

ILoader::lw_label_data_ptr_vect_t Loader::getData() {
    return mData;
}

void Loader::getDirectoryContent(const ILoader::lw_label_path_ptr_t &t) {
    if(t == nullptr) {
        throw std::invalid_argument("Nullptr in Line: " + std::to_string(__LINE__) + " of File: " + __FILE__);
    }
    if (!std::filesystem::exists(t->getPath())) {
        throw std::invalid_argument("Directory requested does not Exist/ In Line: " + std::to_string(__LINE__) + " of File: " + __FILE__);
    }

    for (auto &file : std::filesystem::directory_iterator(std::filesystem::path(t->getPath()))) {
        if (std::filesystem::is_regular_file(file) && (file.path().extension() == ".png" || file.path().extension() == ".jpg")) {
            mData.emplace_back(std::make_shared<LabelDataType>(t->getLabel(), file));
        }
    }
}
