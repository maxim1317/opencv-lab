// Copyright 2019 SnesarevMS

#include "opencv2/opencv.hpp"
#include "opencv2/core.hpp"


int main(int argc, char** argv) {
    std::string path;
    std::string def = "../../pics/river.jpg";  // Default path, doesn't work on Windows

    // Getting image path
    if (argc == 2) {
        path = argv[1];
    }
    else {
        path = def;
    }

    cv::Mat img, image;
    img = cv::imread(path);
    cv::resize(img, image, cv::Size(512, 512));

    std::vector<cv::Mat> rgb, out_rgb;
    cv::split(image, rgb);

    out_rgb.resize(3);
    out_rgb[0] = cv::Mat::zeros(rgb[0].rows * 2, rgb[0].cols * 2, CV_8UC1);
    out_rgb[1] = cv::Mat::zeros(rgb[1].rows * 2, rgb[1].cols * 2, CV_8UC1);
    out_rgb[2] = cv::Mat::zeros(rgb[2].rows * 2, rgb[2].cols * 2, CV_8UC1);
    cv::Rect rect = cv::Rect(0, 0, rgb[0].cols, rgb[0].rows);
    {
        rgb[0].copyTo(out_rgb[0](rect));
        rgb[1].copyTo(out_rgb[1](rect));
        rgb[2].copyTo(out_rgb[2](rect));

        rect.x += rgb[0].cols;
        rgb[2].copyTo(out_rgb[2](rect));

        rect.y += rgb[0].rows;
        rgb[1].copyTo(out_rgb[1](rect));

        rect.x -= rgb[0].cols;
        rgb[0].copyTo(out_rgb[0](rect));
    }

    cv::Mat out_img;

    cv::merge(out_rgb, out_img);

    cv::imshow("vai", out_img);

    cv::waitKey(0);

    return 0;
}
