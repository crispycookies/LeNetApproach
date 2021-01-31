/**
 * @file LeNet.h
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

#ifndef LENET_LENET_H
#define LENET_LENET_H

#include "Object.h"
#include "Loader/ILoader.h"

#include <dlib/opencv.h>
#include <dlib/dnn.h>

#include <utility>

template<typename cvType, typename dlibType = unsigned char>
class [[maybe_unused]] LeNet : public Object {
protected:
    /*Parameterize through templates*/
    using LENET = dlib::loss_multiclass_log<
            dlib::fc<10,
                    dlib::relu<dlib::fc<84,
                            dlib::relu<dlib::fc<120,
                                    dlib::max_pool<2, 2, 2, 2, dlib::relu<dlib::con<16, 5, 5, 1, 1,
                                            dlib::max_pool<2, 2, 2, 2, dlib::relu<dlib::con<6, 5, 5, 1, 1,
                                                    dlib::input<dlib::matrix<dlibType>>>>>>>>>>>>>>;

    ILoader::lw_label_data_ptr_vect_t mData;
    std::map<std::string, unsigned long> mConverter;

    typedef std::vector<cv::Mat> ln_data_vect_t;
    typedef std::vector<unsigned long> ln_label_vect_t;
    typedef std::vector<dlib::matrix<dlibType>> ln_data_dlib_vect_t;

    ln_data_vect_t mPreparedData;
    ln_label_vect_t mLabels;

    virtual void fillConverter() {
        if (mData.empty()) {
            throw std::logic_error("Empty Data in Line" + std::to_string(__LINE__) + " of File: " + __FILE__);
        }
        auto counter = 0;
        for (auto &i : mData) {
            if (i == nullptr) {
                throw std::invalid_argument("Nullptr in Line: " + std::to_string(__LINE__) + " of File: " + __FILE__);
            }
            if (!mConverter.contains(i->getLabel())) {
                mConverter[i->getLabel()] = counter++;
            }
        }
    }

    virtual std::pair<ln_data_vect_t, ln_label_vect_t>
    createLabelAndDataVect(const ILoader::lw_label_data_ptr_vect_t &loc_data) {
        auto data = ln_data_vect_t();
        auto labels = ln_label_vect_t();

        if (loc_data.empty()) {
            throw std::logic_error("Empty Data in Line" + std::to_string(__LINE__) + " of File: " + __FILE__);
        }

        for (auto &i : loc_data) {
            if (i == nullptr) {
                throw std::invalid_argument("Nullptr in Line: " + std::to_string(__LINE__) + " of File: " + __FILE__);
            }
            if (!mConverter.contains(i->getLabel())) {
                throw std::invalid_argument(
                        "Converter does not Contain Keyword: " + std::to_string(__LINE__) + " of File: " + __FILE__);
            }
            data.emplace_back(i->getData());
            labels.emplace_back(mConverter[i->getLabel()]);
        }
        return {data, labels};
    }

    LENET mNet;

    const std::string mSyncFile;

    ln_data_dlib_vect_t prepareFromOpenCV(ln_data_vect_t vector) {
        auto d = ln_data_dlib_vect_t();

        for (auto &v : vector) {
            dlib::matrix<dlibType> d_mat;
            dlib::assign_image(d_mat, dlib::cv_image<cvType>(v));
            d.emplace_back(d_mat);
        }

        return d;
    }

public:
    [[maybe_unused]] explicit LeNet(ILoader::lw_label_data_ptr_vect_t data, std::string sync_file) : mData(
            std::move(data)),
                                                                                                     mSyncFile(
                                                                                                             std::move(
                                                                                                                     sync_file)) {};

    [[maybe_unused]] virtual void makeLabelFromData() {
        fillConverter();
        auto[data, labels] = createLabelAndDataVect(mData);
        mPreparedData = data;
        mLabels = labels;
    }


    [[maybe_unused]] virtual void train() {
        dlib::dnn_trainer<LENET> trainer(mNet);
        trainer.set_learning_rate(0.01);
        trainer.set_min_learning_rate(0.00001);
        trainer.set_mini_batch_size(128);
        trainer.set_iterations_without_progress_threshold(50);
        trainer.set_max_num_epochs(2000);
        trainer.be_verbose();

        trainer.set_synchronization_file(mSyncFile, std::chrono::seconds(20));

        auto data = prepareFromOpenCV(mPreparedData);

        std::cout << "This may take a long ass time..." << std::endl;

        trainer.train(data, mLabels);
    }

    [[maybe_unused]] virtual unsigned long predict(const ILoader::lw_label_data_ptr_t &ptr) {
        if (ptr == nullptr) {
            throw std::logic_error("Nullptr in Line: " + std::to_string(__LINE__) + " of File: " + __FILE__);
        }
        dlib::matrix<dlibType> d_mat;
        dlib::assign_image(d_mat, dlib::cv_image<cvType>(ptr->getData()));

        return mNet(d_mat);
    }

    [[maybe_unused]] virtual std::optional<std::string> resolve(unsigned long value) {
        if(value > mConverter.size()){
            throw std::logic_error("Value to Resolve too large/In Line: " + std::to_string(__LINE__) + " of File: " + __FILE__);
        }
        for (auto it = mConverter.begin(); it != mConverter.end(); ++it) {
            if (it->second == value) {
                return it->first;
            }
        }
        return std::nullopt;
    }

    [[maybe_unused]] virtual void saveNet(const std::string &file) {
        if (file.empty()) {
            throw std::invalid_argument(
                    "Filename Empty in Line: " + std::to_string(__LINE__) + " of File: " + __FILE__);
        }
        dlib::serialize(file) << mNet;
    }

    [[maybe_unused]] virtual void readNet(const std::string &file) {
        if (file.empty()) {
            throw std::invalid_argument(
                    "Filename Empty in Line: " + std::to_string(__LINE__) + " of File: " + __FILE__);
        }
        dlib::deserialize(file) >> mNet;
    }

    ~LeNet() override = default;
};


#endif //LENET_LENET_H
