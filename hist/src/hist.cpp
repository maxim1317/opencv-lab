#include "headers/hist.h"


// Returns cv::Mat with plotted histogram of
// 4 channels: Luminosity(Greyscale), Red, Green and Blue
//
// Arguments:
//     std::vector<cv::Mat> data - data for all 4 channels + x values in format:
//        data[0] - x, values from 0 to 255
//        data[1] - L   \
//        data[2] - R == \ per channel histograms as cv::Mat N:1
//        data[3] - G == /        with values as doubles
//        data[4] - B   /
//
cv::Mat plot_hist(std::vector<cv::Mat> data) {

    cv::Mat x, yL, yR, yG, yB;
    cv::Mat plot_resultL, plot_resultR, plot_resultG, plot_resultB;

    cv::Mat3b plot_result(1024, 512, cv::Vec3b(0, 0, 0));

    x  = data[0];
    yL = data[1];
    yR = data[2];
    yG = data[3];
    yB = data[4];

    double maxY = 0;

    for (int i = 0; i < 256; ++i)
    {
        if (maxY < yL.at<double>(i))
            maxY = yL.at<double>(i);

        if (maxY < yR.at<double>(i))
            maxY = yR.at<double>(i);
        if (maxY < yG.at<double>(i))
            maxY = yG.at<double>(i);
        if (maxY < yB.at<double>(i))
            maxY = yB.at<double>(i);
    }

    cv::Ptr<cv::plot::Plot2d> plotL, plotR, plotG, plotB;

    plotL = cv::plot::Plot2d::create(x, yL);

    plotR = cv::plot::Plot2d::create(x, yR);
    plotG = cv::plot::Plot2d::create(x, yG);
    plotB = cv::plot::Plot2d::create(x, yB);

    plotL->setPlotBackgroundColor(cv::Vec3b( 56,  50,  38));
    plotR->setPlotBackgroundColor(cv::Vec3b( 56,  50,  38));
    plotG->setPlotBackgroundColor(cv::Vec3b( 56,  50,  38));
    plotB->setPlotBackgroundColor(cv::Vec3b( 56,  50,  38));

    plotL->setPlotGridColor(cv::Vec3b(31 , 151, 253));
    plotR->setPlotGridColor(cv::Vec3b(31 , 151, 253));
    plotG->setPlotGridColor(cv::Vec3b(31 , 151, 253));
    plotB->setPlotGridColor(cv::Vec3b(31 , 151, 253));

    plotL->setPlotTextColor(cv::Vec3b(255, 255, 255));
    plotR->setPlotTextColor(cv::Vec3b(255, 255, 255));
    plotG->setPlotTextColor(cv::Vec3b(255, 255, 255));
    plotB->setPlotTextColor(cv::Vec3b(255, 255, 255));

    plotL->setPlotAxisColor(cv::Vec3b(31 , 151, 253));
    plotR->setPlotTextColor(cv::Vec3b(255, 255, 255));
    plotG->setPlotTextColor(cv::Vec3b(255, 255, 255));
    plotB->setPlotTextColor(cv::Vec3b(255, 255, 255));

    plotL->setPlotLineColor(cv::Vec3b(224, 224, 224));
    plotR->setPlotLineColor(cv::Vec3b( 56,  38, 215));
    plotG->setPlotLineColor(cv::Vec3b(108, 221,  83));
    plotB->setPlotLineColor(cv::Vec3b(228, 198,  40));

    plotL->setPlotLineWidth(2);
    plotR->setPlotLineWidth(2);
    plotG->setPlotLineWidth(2);
    plotB->setPlotLineWidth(2);

    plotL->setShowGrid(false);
    plotR->setShowGrid(false);
    plotG->setShowGrid(false);
    plotB->setShowGrid(false);

    plotL->setShowText(false);
    plotR->setShowText(false);
    plotG->setShowText(false);
    plotB->setShowText(false);

    plotL->setInvertOrientation(true);
    plotR->setInvertOrientation(true);
    plotG->setInvertOrientation(true);
    plotB->setInvertOrientation(true);

    plotL->setMinX(0);
    plotR->setMinX(0);
    plotG->setMinX(0);
    plotB->setMinX(0);

    plotL->setMinY(0);
    plotR->setMinY(0);
    plotG->setMinY(0);
    plotB->setMinY(0);

    plotL->setMaxY(maxY * 3 / 2);
    plotR->setMaxY(maxY * 3 / 2);
    plotG->setMaxY(maxY * 3 / 2);
    plotB->setMaxY(maxY * 3 / 2);

    plotL->setMaxX(255);
    plotR->setMaxX(255);
    plotG->setMaxX(255);
    plotB->setMaxX(255);

    plotL->setPlotSize(1024, 512);
    plotR->setPlotSize(1024, 512);
    plotG->setPlotSize(1024, 512);
    plotB->setPlotSize(1024, 512);
    // plotL->setInvertOrientation(true);
    // plotL->setShowText(false);

    plotL->render(plot_resultL);
    plotR->render(plot_resultR);
    plotG->render(plot_resultG);
    plotB->render(plot_resultB);

    plot_result = plot_resultL;

    std::vector<cv::Mat> rgb_plots;

    rgb_plots.push_back(plot_resultR);
    rgb_plots.push_back(plot_resultG);
    rgb_plots.push_back(plot_resultB);

    cv::Vec3b red(  215,  38,  56);
    cv::Vec3b green( 83, 221, 108);
    cv::Vec3b blue(  40, 198, 228);

    std::vector<cv::Vec3b> rgb;

    rgb.push_back(red);
    rgb.push_back(green);
    rgb.push_back(blue);

    for (int i = 0; i < 3; ++i) {
        for (int r = 0; r < 512; ++r) {
            for (int c = 0; c < 1024; ++c) {
                cv::Vec3b color = rgb_plots[i].at<cv::Vec3b>(r, c);
                if (color.val[1] == rgb[i][1]) {
                    plot_result.at<cv::Vec3b>(r, c) = rgb_plots[i].at<cv::Vec3b>(r, c);
                }
            }
        }
    }


    // cv::flip(plot_result, plot_result, 0);

    cv::imwrite("../steps/hist.png", plot_result);

    return plot_result;

}



// Returns std::vector of cv::Mat with histograms
// for all 4 channels + x values in format:
//    data[0] - x, cv::Mat N:1 with values from 0 to 255
//    data[1] - L   \
//    data[2] - R == \ per channel histograms as cv::Mat N:1
//    data[3] - G == /        with values as doubles
//    data[4] - B   /
//
// Arguments:
//     std::string path - path to the image
//
std::vector<cv::Mat> get_hist(const std::string path) {

    std::vector<cv::Mat> hist;

    cv::Mat X(1, 256, CV_64FC1);

    for (int i = 0; i < 256; ++i){
        X.at<double>(i) = i;
    }

    cv::Mat L = cv::Mat::zeros(1, 256, CV_64FC1);

    cv::Mat G = cv::Mat::zeros(1, 256, CV_64FC1);
    cv::Mat B = cv::Mat::zeros(1, 256, CV_64FC1);
    cv::Mat R = cv::Mat::zeros(1, 256, CV_64FC1);

    cv::Mat3b image = cv::imread(path, cv::IMREAD_COLOR);

    if (image.channels() == 3)
    {
        std::string ty =  type2str( image.type() );
        printf("Image: %s %dx%d \n", ty.c_str(), image.cols, image.rows );

        for (int r = 0; r < image.rows; ++r) {
            for (int c = 0; c < image.cols; ++c) {
                cv::Vec3b intensity = image.at<cv::Vec3b>(r, c);
                B.at<double>(intensity.val[0]) += 1;
                G.at<double>(intensity.val[1]) += 1;
                R.at<double>(intensity.val[2]) += 1;
            }
        }
    }

    cv::Mat1b grey_image;
    cv::cvtColor (image, grey_image, cv::COLOR_BGR2GRAY);

    for (int r = 0; r < grey_image.rows; ++r)
        for (int c = 0; c < grey_image.cols; ++c)
            L.at<double>(grey_image(r, c)) += 1;
    // etc...

    hist.push_back(X);


    for (int i = 0; i < 256; ++i)
    {
        L.at<double>(i) = log10(L.at<double>(i));

        R.at<double>(i) = log10(R.at<double>(i));
        G.at<double>(i) = log10(G.at<double>(i));
        B.at<double>(i) = log10(B.at<double>(i));
    }


    hist.push_back(L);

    hist.push_back(R);
    hist.push_back(G);
    hist.push_back(B);

    return hist;
}

int main(int argc, char const *argv[]) {

    std::string path;
    std::string def = "../../pics/logo.jpg";  // Default path, doesn't work on Windows

    // Getting image path
    if (argc == 2) {
        path = argv[1];
    }
    else {
        path = def;
    }

    // Calculating histogram
    std::vector<cv::Mat> hist;
    hist = get_hist(path);

    // Exporting data for gnuplot (or visual analysis)
    exp_gnu("../plot/luminosity.txt", hist);

    // Reading and resising image
    cv::Mat3b image = cv::imread(path, cv::IMREAD_COLOR);

    cv::Mat3b resized_image;
    cv::resize(image, resized_image, cv::Size(512, 512));

    // Plotting histogram
    cv::Mat hist_plot;
    hist_plot = PlotGraph(hist);

    // Merging image and histogram
    int rows = resized_image.rows;
    int cols = resized_image.cols + hist_plot.cols;

    cv::Mat3b merged_img(rows, cols, cv::Vec3b(0, 0, 0));

    resized_image.copyTo(merged_img(cv::Rect(0, 0, resized_image.cols, resized_image.rows)));
    hist_plot.copyTo(merged_img(cv::Rect(resized_image.cols, 0, hist_plot.cols, hist_plot.rows)));

    // Showing final result
    cv::namedWindow("Histogram", cv::WINDOW_AUTOSIZE);
    cv::imshow("Histogram", merged_img);
    cv::waitKey(0);

    // Writing steps to steps directory
    cv::imwrite("../steps/resized.png", resized_image);
    cv::imwrite("../steps/merged.png", merged_img);

    return 0;
}
