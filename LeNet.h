//
// Created by tobi on 30.01.21.
//

#ifndef LENET_LENET_H
#define LENET_LENET_H

#include "Object.h"
#include "Loader/ILoader.h"

#include <dlib/dnn.h>

#include <utility>

class [[maybe_unused]] LeNet : public Object {
protected:
    /*Parameterize through templates*/
    using LENET [[maybe_unused]] = dlib::loss_multiclass_log<
            dlib::fc<10,
                    dlib::relu<dlib::fc<84,
                            dlib::relu<dlib::fc<120,
                                    dlib::max_pool<2, 2, 2, 2, dlib::relu<dlib::con<16, 5, 5, 1, 1,
                                            dlib::max_pool<2, 2, 2, 2, dlib::relu<dlib::con<6, 5, 5, 1, 1,
                                                    dlib::input<dlib::matrix<unsigned char>>>>>>>>>>>>>>;

    ILoader::lw_label_data_ptr_vect_t mData;
    std::map<std::string, int> mConverter;

    typedef std::vector<cv::Mat> ln_data_vect_t;
    typedef std::vector<int> ln_label_vect_t;

    ln_data_vect_t mPreparedData;
    ln_label_vect_t mLabels;

    virtual void fillConverter();

    virtual std::pair<ln_data_vect_t, ln_label_vect_t>
    createLabelAndDataVect(const ILoader::lw_label_data_ptr_vect_t &loc_data);

public:
    explicit LeNet(ILoader::lw_label_data_ptr_vect_t data) : mData(std::move(data)) {};

    virtual void makeLabelFromData();

    virtual void train();

    virtual void predict();

    ~LeNet() override = default;
};


#endif //LENET_LENET_H
