/**
 * @file Loader.h
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
