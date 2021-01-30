//
// Created by tobi on 30.01.21.
//

#include "LeNet.h"

void LeNet::makeLabelFromData() {
    fillConverter();
    auto [data, labels] = createLabelAndDataVect(mData);
    mPreparedData = data;
    mLabels = labels;
}

void LeNet::train() {

}

void LeNet::predict() {

}

void LeNet::fillConverter() {
    if(mData.empty()){
        throw std::logic_error("Empty Data in Line" + std::to_string(__LINE__) + " of File: " + __FILE__);
    }
    auto counter = 0;
    for(auto & i : mData){
        if(i == nullptr){
            throw std::invalid_argument("Nullptr in Line: " + std::to_string(__LINE__) + " of File: " + __FILE__);
        }
        if(!mConverter.contains(i->getLabel())){
            mConverter[i->getLabel()] = counter++;
        }
    }
}

std::pair<LeNet::ln_data_vect_t, LeNet::ln_label_vect_t>
LeNet::createLabelAndDataVect(const ILoader::lw_label_data_ptr_vect_t &loc_data) {
    auto data = ln_data_vect_t();
    auto labels = ln_label_vect_t();

    if(loc_data.empty()){
        throw std::logic_error("Empty Data in Line" + std::to_string(__LINE__) + " of File: " + __FILE__);
    }

    for(auto & i : loc_data){
        if(i == nullptr){
            throw std::invalid_argument("Nullptr in Line: " + std::to_string(__LINE__) + " of File: " + __FILE__);
        }
        if(!mConverter.contains(i->getLabel())){
            throw std::invalid_argument("Converter does not Contain Keyword: " + std::to_string(__LINE__) + " of File: " + __FILE__);
        }
        data.emplace_back(i->getData());
        labels.emplace_back(mConverter[i->getLabel()]);
    }
    return {data, labels};
}
