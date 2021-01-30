/**
 * @file ILoader.h
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

#ifndef LENET_ILOADER_H
#define LENET_ILOADER_H

#include "../Object.h"
#include "../File/LabelDataType.h"
#include "../Folder/LabelPathType.h"

class [[maybe_unused]] ILoader : private Object {
protected:
    ILoader() = default;
public:
    ~ILoader() override = default;

    [[maybe_unused]] typedef LabelDataType lw_label_data_t;
    [[maybe_unused]] typedef LabelPathType lw_label_path_t;
    typedef std::shared_ptr<lw_label_path_t> lw_label_path_ptr_t;
    typedef std::shared_ptr<lw_label_data_t> lw_label_data_ptr_t;

    typedef std::vector<lw_label_path_ptr_t> lw_label_path_ptr_vect_t;
    typedef std::vector<lw_label_data_ptr_t> lw_label_data_ptr_vect_t;


    [[maybe_unused]] virtual void setPathsWithLabels(const lw_label_path_ptr_vect_t & paths_with_label) = 0;
    [[maybe_unused]] virtual void load() = 0;
    [[maybe_unused]] virtual void commit() = 0;
    [[maybe_unused]] virtual void process(const std::shared_ptr<IProcessor> & processor) = 0;
    [[maybe_unused]] virtual lw_label_data_ptr_vect_t getData() = 0;
};

#endif //LENET_ILOADER_H
