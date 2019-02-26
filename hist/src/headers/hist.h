#ifndef __HIST_H__
#define __HIST_H__

#include "opencv2/opencv.hpp"
#include "opencv2/plot.hpp"
#include <iostream>
#include <algorithm>
#include <numeric>
#include <string>
#include <math.h>

void exp_gnu(const char *, std::vector<cv::Mat>);
std::string type2str(int);

cv::Mat PlotGraph(std::vector<cv::Mat>);
std::vector<cv::Mat> get_hist(const std::string);

#endif
