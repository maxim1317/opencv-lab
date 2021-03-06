//http://docs.opencv.org/modules/core/doc/drawing_functions.html#void line(Mat& img, Point pt1, Point pt2, const Scalar& color, int thickness, int lineType, int shift)

#include <iostream>
#include <string>

#include <opencv2/opencv.hpp>

using namespace cv;

int main() {
    Mat image(Mat::zeros(100, 100, CV_8U));
    imwrite("sample.black.png", image);
    image = Mat::ones(400, 400, CV_8U);
    imwrite("sample.ones.png", image);
    image += Scalar(255);
    imwrite("sample.white.png", image);

    circle(image, Point(20, 20), 30, Scalar(100));
    circle(image, Point(60, 20), 30, Scalar(100), 1, 4);
    circle(image, Point(40, 40), 15, Scalar(50), 4, 8);
    circle(image, Point(60, 60), 24, Scalar(0), 1, 4);
    imwrite("sample.circles.png", image);

    return 0;
}
