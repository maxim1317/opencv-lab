#ifndef __MISC_CPP__
#define __MISC_CPP__

#include "hist.h"

void exp_gnu(const char *file, std::vector<cv::Mat> hist) {
    FILE *out;
    out = fopen(file, "w");
    if (!out) {
        printf("\
            Broken lines, broken strings\n\
            Broken threads, broken springs\n\
            Broken idols, broken heads\n\
            People sleeping in broken beds\n\
            Ain't no use jiving\n\
            Ain't no use joking\n\
            EVERYTHING IS BROKEN\n\n\n\n\
            Seriously though, this error should never be shown\n\
            If you are a user, god speed\n\
            Ẻ̵͎͓̕x̸̛̜̯͑i̴̳̇̕t̸̻̦̊̃ ̵͈͈̂w̸͔̍h̵̭͌ͅĩ̷̠̽l̷̻̠͌̒ë̴̻́ ̸̺̮̒̾y̵͉̌ȯ̷͉̻ü̴͍̟ ̸͓̬̂͋c̶̛̖ȧ̵̀͜n̵̓̒͜\n\
        ");

        return;
    }
    for (int i = 0; i < 256; i++) {
        fprintf(out, "%f %f %f %f %f\n", hist[0].at<double>(i), hist[1].at<double>(i), hist[2].at<double>(i), hist[3].at<double>(i), hist[4].at<double>(i));
    }
    fclose(out);

    printf("Exported to %s\n", file);
}

std::string type2str(int type) {
    std::string r;

    uchar depth = type & CV_MAT_DEPTH_MASK;
    uchar chans = 1 + (type >> CV_CN_SHIFT);

    switch ( depth ) {
        case CV_8U:  r = "8U";   break;
        case CV_8S:  r = "8S";   break;
        case CV_16U: r = "16U";  break;
        case CV_16S: r = "16S";  break;
        case CV_32S: r = "32S";  break;
        case CV_32F: r = "32F";  break;
        case CV_64F: r = "64F";  break;
        default:     r = "User"; break;
    }

    r += "C";
    r += (chans+'0');

    return r;
}

#endif