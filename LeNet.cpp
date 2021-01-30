/**
 * @file LeNet.cpp
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
#include "LeNet.h"
#include <dlib/opencv.h>

[[maybe_unused]] void LeNet::makeLabelFromData() {
    fillConverter();
    auto [data, labels] = createLabelAndDataVect(mData);
    mPreparedData = data;
    mLabels = labels;
}

[[maybe_unused]] void LeNet::train() {
    dlib::dnn_trainer<LENET> trainer(mNet);
    trainer.set_learning_rate(0.01);
    trainer.set_min_learning_rate(0.00001);
    trainer.set_mini_batch_size(128);
    trainer.be_verbose();

    trainer.set_synchronization_file(mSyncFile, std::chrono::seconds(20));

    std::cout << "This may take a long ass time..." << std::endl;

    //trainer.train(mPreparedData, mLabels);
}

[[maybe_unused]] void LeNet::predict() {

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

[[maybe_unused]] void LeNet::saveNet(const std::string &file) {
    if(file.empty()){
        throw std::invalid_argument("Filename Empty in Line: " + std::to_string(__LINE__) + " of File: " + __FILE__);
    }
    dlib::serialize(file) << mNet;
}

