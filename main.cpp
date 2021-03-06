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

#include "ImgShow.h"

template<typename T, typename T2>
auto predict(const ILoader::lw_label_data_ptr_t &d, const std::shared_ptr<LeNet<T, T2>> &lnet) {
    if (lnet == nullptr) {
        throw std::invalid_argument("Nullptr in Line: " + std::to_string(__LINE__) + " of File: " + __FILE__);
    }
    if (d == nullptr) {
        throw std::invalid_argument("Nullptr in Line: " + std::to_string(__LINE__) + " of File: " + __FILE__);
    }
    auto p = lnet->predict(d);
    auto s = lnet->resolve(p);
    return s;
}

template<typename T, typename T2>
void verify(const ILoader::lw_label_data_ptr_vect_t &data, const std::shared_ptr<LeNet<T, T2>> &lnet) {
    if (data.empty()) {
        throw std::logic_error("data Empty in Line: " + std::to_string(__LINE__) + " of File: " + __FILE__);
    }
    if (lnet == nullptr) {
        throw std::invalid_argument("Nullptr in Line: " + std::to_string(__LINE__) + " of File: " + __FILE__);
    }

    fl_message_title("Use console?");
    bool use_console = fl_choice("Do you want to print the result to console rather than using a GUI?", "No", "Yes", 0);

#ifdef _WIN32
    if(!use_console)
        FreeConsole();
#endif

    for (auto &i : data) {
        if (i == nullptr) {
            throw std::invalid_argument("Nullptr in Line: " + std::to_string(__LINE__) + " of File: " + __FILE__);
        }
        auto p = predict(i, lnet);

        std::stringstream strstr;
        strstr << "#############################################" << std::endl;
        strstr << "File #" << i->getPath().string() << std::endl;
        if (p == std::nullopt) {
            strstr << "Prediction #" << "NaN" << std::endl;
        } else {
            strstr << "Prediction #" << p.value() << std::endl;
        }
        strstr << "#############################################" << std::endl;
        if(use_console){
            std::cout << strstr.str();
	}
        else{
            ImgShow a(i->getData(), "Picture", ImgShow::rgb, false);
            fl_message_title("Result");
            fl_message(strstr.str().c_str());
        }
    }
}

auto load(const ILoader::lw_label_path_ptr_vect_t &paths) {
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

template<typename T, typename T2>
void validate(const std::shared_ptr<LeNet<T, T2>> &lnet) {
    if (lnet == nullptr) {
        throw std::invalid_argument("Nullptr in Line: " + std::to_string(__LINE__) + " of File: " + __FILE__);
    }
    auto validation_all = ILoader::lw_label_path_ptr_vect_t();

    validation_all.push_back(std::make_shared<LabelPathType>(
            std::filesystem::path("../pic/All/"),
            "All"));
    validation_all.push_back(std::make_shared<LabelPathType>(
            std::filesystem::path(
                    "../pic/Combinations/"),
            "Combination"));
    validation_all.push_back(std::make_shared<LabelPathType>(
            std::filesystem::path("../pic/Other/"),
            "Other"));

    verify(load(validation_all), lnet);
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
    try {
        // wm icon
        auto icon = std::make_shared<Fl_RGB_Image>(icon_data, 128, 128, ImgShow::fl_imgtype::rgba, 0);
        ((Fl_Double_Window*)fl_message_icon()->parent())->icon(icon.get());

        auto pathsWithLabels = ILoader::lw_label_path_ptr_vect_t();

        pathsWithLabels.push_back(std::make_shared<LabelPathType>(
                std::filesystem::path("../pic/0-Normal/"),
                "Normal"));
        pathsWithLabels.push_back(std::make_shared<LabelPathType>(
                std::filesystem::path("../pic/1-NoHat/"),
                "NoHat"));
        pathsWithLabels.push_back(std::make_shared<LabelPathType>(
                std::filesystem::path("../pic/2-NoFace/"),
                "NoFace"));
        pathsWithLabels.push_back(std::make_shared<LabelPathType>(
                std::filesystem::path("../pic/3-NoLeg/"),
                "NoLeg"));
        pathsWithLabels.push_back(std::make_shared<LabelPathType>(
                std::filesystem::path(
                        "../pic/4-NoBodyPrint/"),
                "NoBodyPrint"));
        pathsWithLabels.push_back(std::make_shared<LabelPathType>(
                std::filesystem::path("../pic/5-NoHand/"),
                "NoHand"));
        pathsWithLabels.push_back(std::make_shared<LabelPathType>(
                std::filesystem::path("../pic/6-NoHead/"),
                "NoHead"));
        pathsWithLabels.push_back(std::make_shared<LabelPathType>(
                std::filesystem::path("../pic/7-NoArm/"),
                "NoArm"));

        auto f = load(pathsWithLabels);
        auto lnet = std::make_shared<LeNet<dlib::bgr_pixel, unsigned char>>(f, "../Model/indie_sync_file.sync");

        lnet->makeLabelFromData();
        lnet->train();
        lnet->saveNet("../Model/indie_file_model.mod");
        lnet->readNet("../Model/indie_file_model.mod");

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


    return(Fl::run());
}
