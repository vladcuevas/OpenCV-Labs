#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <time.h>
#include "dataPath.hpp"

using namespace std;
using namespace cv;

void thresholdingUsingForLoop(Mat src, Mat dst, int thresh, int maxValue) {
    int height = src.size().height;
    int width = src.size().width;

    // Loop over rows
    for (int i=0; i < height; i++) {
        // Loop over columns
        for (int j=0; j < width; j++) {
            if (src.at<uchar>(i, j) > thresh)
                dst.at<uchar>(i, j) = maxValue;
            else
                dst.at<uchar>(i, j) = 0;
        }
    }
}


int main() {
    // Read an image in grayscale
    string imagePath = DATA_PATH + "images/threshold.png";
    Mat src = imread(imagePath, IMREAD_GRAYSCALE);

    // Set threshold and maximum value
    int thresh = 100;
    int maxValue = 255;
    imshow("image", src);
    waitKey(0);

    Mat dst = src.clone();
    clock_t t;
    double cpu_time_used;

    t = clock();
    thresholdingUsingForLoop(src, dst, thresh, maxValue);
    t = clock()-t;
    cpu_time_used = ((double)t) / CLOCKS_PER_SEC;
    cout << "Time taken with Manual Algorithm = " << cpu_time_used << endl;

    imshow("image", dst);
    waitKey(0);

    t = clock();
    threshold(src, dst, thresh, maxValue, THRESH_BINARY);
    t = clock()-t;
    cpu_time_used = ((double)t) / CLOCKS_PER_SEC;
    cout << "Time taken = " << cpu_time_used << endl;

    imshow("image", dst);
    waitKey(0);

    clock_t t_loop, t_opencv;
    double time_opencv = 0;
    double time_loops = 0;
    double n_samples = 10.0;

    for (int i=0; i < (int)n_samples; i++) {
        t = clock();
        thresholdingUsingForLoop(src, dst, thresh, maxValue);
        t = clock()-t;
        t_loop += t;

        t = clock();
        threshold(src, dst, thresh, maxValue, THRESH_BINARY);
        t = clock() - t;
        t_opencv += t;
    }

    time_opencv = t_opencv/(n_samples*CLOCKS_PER_SEC);
    time_loops = t_loop/(n_samples*CLOCKS_PER_SEC);

    cout << "Average time taken by For Loop Code = " << time_loops << " seconds" << endl;
    cout << "Average time taken by OpenCV Code = " << time_opencv << " seconds" << endl;

    thresh = 100;
    maxValue = 150;

    Mat dst_bin;
    threshold(src, dst_bin, thresh, maxValue, THRESH_BINARY);
    cout << "threshold(src, dst_bin, thresh, maxValue, THRESH_BINARY);" << endl;

    imshow("image", dst_bin);
    waitKey(0);

    Mat dst_bin_inv;
    threshold(src, dst_bin_inv, thresh, maxValue, THRESH_BINARY_INV);
    cout << "threshold(src, dst_bin, thresh, maxValue, THRESH_BINARY_INV);" << endl;

    imshow("image", dst_bin_inv);
    waitKey(0);

    Mat dst_trunc;
    threshold(src, dst_trunc, thresh, maxValue, THRESH_TRUNC);
    cout << "threshold(src, dst_bin, thresh, maxValue, THRESH_TRUNC);" << endl;

    imshow("image", dst_trunc);
    waitKey(0);

    Mat dst_to_zero;
    threshold(src, dst_to_zero, thresh, maxValue, THRESH_TOZERO);
    cout << "threshold(src, dst_bin, thresh, maxValue, THRESH_TOZERO);" << endl;

    imshow("image", dst_to_zero);
    waitKey(0);

    Mat dst_to_zero_inv;
    threshold(src, dst_to_zero_inv, thresh, maxValue, THRESH_TOZERO_INV);
    cout << "threshold(src, dst_bin, thresh, maxValue, THRESH_TOZERO_INV);" << endl;

    imshow("image", dst_to_zero_inv);
    waitKey(0);

    return 0;
}
