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

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
    try {
        auto dummy_processor = std::make_shared<DummyProcessor>();

        auto loader = std::make_shared<Loader>();
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
                std::filesystem::path("/home/tobi/Dokumente/FH/DIP/Abgabe/LENET/cpp/project_lego_indie/pic/4-NoBodyPrint/"),
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

        loader->setPathsWithLabels(pathsWithLabels);
        loader->load();
        loader->commit();
        loader->process(dummy_processor);

        auto f = loader->getData();

        auto lnet = LeNet<dlib::bgr_pixel, unsigned char>(f,"indie_sync_file.sync");
        lnet.makeLabelFromData();
        lnet.train();
        lnet.saveNet("indie_file_model.mod");
        lnet.readNet("indie_file_model.mod");
        lnet.predict(nullptr);
    } catch (const std::invalid_argument &exe) {
        std::cerr << exe.what() << std::endl;
        return EXIT_FAILURE;
    }
    catch (const std::logic_error &exe) {
        std::cerr << exe.what() << std::endl;
        return EXIT_FAILURE;
    }
    catch (const std::exception & exe){
        std::cerr << exe.what() << std::endl;
        return EXIT_FAILURE;
    }
    catch (...) {
        std::cerr << "Unknown Error Occured" << std::endl;
        return EXIT_FAILURE;
    }


    return EXIT_SUCCESS;
}
