#ifndef __HIST_H__
#define __HIST_H__

#include "opencv2/opencv.hpp"
#include "opencv2/plot.hpp"  // Plot2d from opencv_contrib

#include <iostream>
#include <string>
#include <math.h>

// From misc.cpp
void exp_gnu(const char *, std::vector<cv::Mat>);   // Exports data to gnuplot format
std::string type2str(int);                          // Converts int to cv-style image format

std::vector<cv::Mat> get_hist(const std::string);   // Calculates histogram
cv::Mat plot_hist(std::vector<cv::Mat>);            // Plots histogram

#endif
