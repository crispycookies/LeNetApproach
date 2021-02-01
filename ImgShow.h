
/**
 * @file ImgShow.h
 * @brief Helper class to display opencv matrix containing a image data.
 * @author Daniel Giritzer, Tobias Egger
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

#ifndef IMGSHOW_H
#define IMGSHOW_H

// FLTK
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_RGB_Image.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_File_Chooser.H>
#include <FL/fl_ask.H>

// OpenCV
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>


#include "Icon.h"

/**
 * Helper class to display opencv matrix containing a image data.
 */
class ImgShow {
public:

    enum fl_imgtype{
        grey =  1,
        greya = 2,
        rgb =   3,
        rgba =  4
    };

    /**
     * @param img OpenCV matrix containing image data
     * @param title Title to be shown in the window header
     * @param type Image type (use enum from this class namespace)
     * @param rescale if true min and max values of a given grayscale picture are rescaled between 0-255, defaults to false
     * @param showblocking if true picture is shown immidiatly and blocks execution until window is closed.
     */
    ImgShow(const cv::Mat& img, const std::string& title, const ImgShow::fl_imgtype& type, bool rescale = false, bool showblocking = false){

        // Convert image data from BRG (opencv default) to RGB
        if(type == fl_imgtype::rgb || type == fl_imgtype::rgba){
            cv::cvtColor(img, m_ImgRGB, cv::COLOR_BGR2RGB);
        }
        else {
            if(rescale){
                m_ImgRGB = img;
                cv::normalize(m_ImgRGB, m_ImgRGB, 0, 255, cv::NORM_MINMAX, CV_8U);
            }
            else
            {
                if(img.type() != CV_8U)
                    img.convertTo(m_ImgRGB, CV_8U);
                else
                    m_ImgRGB = img;
            }
        }

        m_Win = std::make_shared<Fl_Window>(m_ImgRGB.cols,m_ImgRGB.rows, title.c_str());
        m_Scr = std::make_shared<Fl_Scroll>(0,0,m_Win->w(), m_Win->h());
        m_Pic = std::make_shared<Fl_RGB_Image>(m_ImgRGB.data, m_ImgRGB.cols, m_ImgRGB.rows, type, 0);
        m_Box = std::make_shared<Fl_Box>(0,0, m_Pic->w(), m_Pic->h());
        m_Box->image(m_Pic.get());
        m_Icon = std::make_shared<Fl_RGB_Image>(icon_data, 128, 128, ImgShow::fl_imgtype::rgba, 0);
        m_Win->icon(m_Icon.get());
        m_Win->resizable(m_Box.get()); // some window managers may truncate big windows according their needs, so allow resizing here.
        m_Win->show();

        if(showblocking)
            while(Fl::wait()!=0){}
    }
    virtual ~ImgShow() = default;

private:
    std::shared_ptr<Fl_Window> m_Win;
    std::shared_ptr<Fl_Scroll> m_Scr;
    std::shared_ptr<Fl_RGB_Image> m_Pic;
    std::shared_ptr<Fl_RGB_Image> m_Icon;
    std::shared_ptr<Fl_Box> m_Box;
    cv::Mat m_ImgRGB;
};

#endif // IMGSHOW_H