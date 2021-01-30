/**
 * @file main.cpp
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

#include <iostream>

#include "File/LabelDataType.h"
#include "Processor/DummyProcessor.h"
#include "Loader/Loader.h"

#include "LeNet.h"

template <typename T, typename T2>
auto predict(const ILoader::lw_label_data_ptr_t & d, const std::shared_ptr<LeNet<T, T2>> & lnet){
    if(lnet == nullptr){
        throw std::invalid_argument("Nullptr in Line: " + std::to_string(__LINE__) + " of File: " + __FILE__);
    }
    if(d == nullptr){
        throw std::invalid_argument("Nullptr in Line: " + std::to_string(__LINE__) + " of File: " + __FILE__);
    }
    auto p = lnet->predict(d);
    auto s = lnet->resolve(p);
    return s;
}

template <typename T, typename T2>
void verify(const ILoader::lw_label_data_ptr_vect_t &data, const std::shared_ptr<LeNet<T, T2>> & lnet) {
    if (data.empty()) {
        throw std::logic_error("data Empty in Line: " + std::to_string(__LINE__) + " of File: " + __FILE__);
    }
    if(lnet == nullptr){
        throw std::invalid_argument("Nullptr in Line: " + std::to_string(__LINE__) + " of File: " + __FILE__);
    }
    for (auto &i : data) {
        if (i == nullptr) {
            throw std::invalid_argument("Nullptr in Line: " + std::to_string(__LINE__) + " of File: " + __FILE__);
        }
        auto p = predict(i, lnet);

        std::cout << "#############################################" << std::endl;
        std::cout << "File #" << i->getPath().string() << std::endl;
        if(p == std::nullopt){
            std::cout << "Prediction #" << "NaN" << std::endl;
        }else{
            std::cout << "Prediction #" << p.value() << std::endl;
        }
        std::cout << "#############################################" << std::endl;
    }
}

auto load(const ILoader::lw_label_path_ptr_vect_t & paths){
    if (paths.empty()) {
        throw std::logic_error("data Empty in Line: " + std::to_string(__LINE__) + " of File: " + __FILE__);
    }
    auto loader = std::make_shared<Loader>();
    auto dummy_processor = std::make_shared<DummyProcessor>();

    loader->setPathsWithLabels(paths);
    loader->load();
    loader->commit();
    loader->process(dummy_processor);

    return loader->getData();
}

template <typename T, typename T2>
void validate(const std::shared_ptr<LeNet<T, T2>> & lnet){
    if(lnet == nullptr){
        throw std::invalid_argument("Nullptr in Line: " + std::to_string(__LINE__) + " of File: " + __FILE__);
    }
    auto validation_all = ILoader::lw_label_path_ptr_vect_t();

    validation_all.push_back(std::make_shared<LabelPathType>(
            std::filesystem::path("/home/tobi/Dokumente/FH/DIP/Abgabe/LENET/cpp/project_lego_indie/pic/All/"),
            "All"));
    validation_all.push_back(std::make_shared<LabelPathType>(
            std::filesystem::path(
                    "/home/tobi/Dokumente/FH/DIP/Abgabe/LENET/cpp/project_lego_indie/pic/Combinations/"),
            "Combination"));
    validation_all.push_back(std::make_shared<LabelPathType>(
            std::filesystem::path("/home/tobi/Dokumente/FH/DIP/Abgabe/LENET/cpp/project_lego_indie/pic/Other/"),
            "Other"));

    verify(load(validation_all), lnet);
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
    try {
        auto pathsWithLabels = ILoader::lw_label_path_ptr_vect_t();

        pathsWithLabels.push_back(std::make_shared<LabelPathType>(
                std::filesystem::path("/home/tobi/Dokumente/FH/DIP/Abgabe/LENET/cpp/project_lego_indie/pic/0-Normal/"),
                "Normal"));
        pathsWithLabels.push_back(std::make_shared<LabelPathType>(
                std::filesystem::path("/home/tobi/Dokumente/FH/DIP/Abgabe/LENET/cpp/project_lego_indie/pic/1-NoHat/"),
                "NoHat"));
        pathsWithLabels.push_back(std::make_shared<LabelPathType>(
                std::filesystem::path("/home/tobi/Dokumente/FH/DIP/Abgabe/LENET/cpp/project_lego_indie/pic/2-NoFace/"),
                "NoFace"));
        pathsWithLabels.push_back(std::make_shared<LabelPathType>(
                std::filesystem::path("/home/tobi/Dokumente/FH/DIP/Abgabe/LENET/cpp/project_lego_indie/pic/3-NoLeg/"),
                "NoLeg"));
        pathsWithLabels.push_back(std::make_shared<LabelPathType>(
                std::filesystem::path(
                        "/home/tobi/Dokumente/FH/DIP/Abgabe/LENET/cpp/project_lego_indie/pic/4-NoBodyPrint/"),
                "NoBodyPrint"));
        pathsWithLabels.push_back(std::make_shared<LabelPathType>(
                std::filesystem::path("/home/tobi/Dokumente/FH/DIP/Abgabe/LENET/cpp/project_lego_indie/pic/5-NoHand/"),
                "NoHand"));
        pathsWithLabels.push_back(std::make_shared<LabelPathType>(
                std::filesystem::path("/home/tobi/Dokumente/FH/DIP/Abgabe/LENET/cpp/project_lego_indie/pic/6-NoHead/"),
                "NoHead"));
        pathsWithLabels.push_back(std::make_shared<LabelPathType>(
                std::filesystem::path("/home/tobi/Dokumente/FH/DIP/Abgabe/LENET/cpp/project_lego_indie/pic/7-NoArm/"),
                "NoArm"));

        auto f = load(pathsWithLabels);
        auto lnet = std::make_shared<LeNet<dlib::bgr_pixel, unsigned char>>(f, "indie_sync_file.sync");

        lnet->makeLabelFromData();
        lnet->train();
        lnet->saveNet("indie_file_model.mod");
        lnet->readNet("indie_file_model.mod");

        validate(lnet);
    } catch (const std::invalid_argument &exe) {
        std::cerr << exe.what() << std::endl;
        return EXIT_FAILURE;
    }
    catch (const std::logic_error &exe) {
        std::cerr << exe.what() << std::endl;
        return EXIT_FAILURE;
    }
    catch (const std::exception &exe) {
        std::cerr << exe.what() << std::endl;
        return EXIT_FAILURE;
    }
    catch (...) {
        std::cerr << "Unknown Error Occured" << std::endl;
        return EXIT_FAILURE;
    }


    return EXIT_SUCCESS;
}
