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
                "Indie"));
        pathsWithLabels.push_back(std::make_shared<LabelPathType>(
                std::filesystem::path("/home/tobi/Dokumente/FH/DIP/Abgabe/LENET/cpp/project_lego_indie/pic/1-NoHat/"),
                "Hat"));
        pathsWithLabels.push_back(std::make_shared<LabelPathType>(
                std::filesystem::path("/home/tobi/Dokumente/FH/DIP/Abgabe/LENET/cpp/project_lego_indie/pic/2-NoFace/"),
                "RLeg"));

        loader->setPathsWithLabels(pathsWithLabels);
        loader->load();
        loader->commit();
        loader->process(dummy_processor);

        auto f = loader->getData();

        using LeNet = dlib::loss_multiclass_log<
                dlib::fc<10,
                dlib::relu<dlib::fc<84,
                dlib::relu<dlib::fc<120,
                dlib::max_pool<2, 2, 2, 2, dlib::relu<dlib::con<16, 5, 5, 1, 1,
                dlib::max_pool<2, 2, 2, 2, dlib::relu<dlib::con<6, 5, 5, 1, 1,
                dlib::input<dlib::matrix<unsigned char>>>>>>>>>>>>>>;

        LeNet net;
        dlib::dnn_trainer<LeNet> trainer(net);
        trainer.set_learning_rate(0.01);
        trainer.set_min_learning_rate(0.00001);
        trainer.set_mini_batch_size(128);
        trainer.be_verbose();

        trainer.set_synchronization_file("indie_train_sync", std::chrono::seconds(20));
    } catch (const std::invalid_argument &exe) {
        std::cerr << exe.what() << std::endl;
        return EXIT_FAILURE;
    }
    catch (const std::logic_error &exe) {
        std::cerr << exe.what() << std::endl;
        return EXIT_FAILURE;
    }
    catch (...) {
        std::cerr << "Unknown Error Occured" << std::endl;
        return EXIT_FAILURE;
    }


    return EXIT_SUCCESS;
}
