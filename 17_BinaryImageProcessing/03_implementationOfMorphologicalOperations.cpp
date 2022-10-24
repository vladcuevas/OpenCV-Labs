#include <iostream>
#include "dataPath.hpp"
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <time.h>

using namespace std;
using namespace cv;

int main()
{
    Mat demoImage = Mat::zeros(Size(10, 10), CV_8U);

    cout << demoImage << endl;

    imshow("image", demoImage);
    waitKey(0);

    demoImage.at<uchar>(0, 1) = 1;
    demoImage.at<uchar>(9, 0) = 1;
    demoImage.at<uchar>(8, 9) = 1;
    demoImage.at<uchar>(2, 2) = 1;
    demoImage(Range(5, 8), Range(5, 8)).setTo(1);
    cout << demoImage << endl;

    imshow("image", demoImage * 255);
    waitKey(0);

    Mat element = getStructuringElement(MORPH_CROSS, Size(3, 3));
    cout << element;
    int ksize = element.size().height;
    int height, width;
    height = demoImage.size().height;
    width = demoImage.size().width;

    int border = ksize / 2;
    Mat paddedDemoImage = Mat::zeros(Size(height + border * 2, width + border * 2), CV_8UC1);
    copyMakeBorder(paddedDemoImage, paddedDemoImage, border, border, border, border, BORDER_CONSTANT, 0);
    Mat bitOR;

    for (int h_i = border; h_i < height + border; h_i++)
    {
        for (int w_i = border; w_i < width + border; w_i++)
        {
            if (demoImage.at<uchar>(h_i - border, w_i - border))
            {
                cout << "White Pixel Found @ " << h_i << "," << w_i << endl;
                cout << paddedDemoImage(Range(h_i - border, h_i + border + 1),
                                        Range(w_i - border, w_i + border + 1))
                     << endl;
                cout << element << endl;
                bitwise_or(paddedDemoImage(Range(h_i - border, h_i + border + 1),
                                           Range(w_i - border, w_i + border + 1)),
                           element, bitOR);
                cout << bitOR << endl;
                cout << paddedDemoImage(Range(h_i - border, h_i + border + 1),
                                        Range(w_i - border, w_i + border + 1))
                     << endl;
                bitOR.copyTo(paddedDemoImage(Range(h_i - border, h_i + border + 1),
                                             Range(w_i - border, w_i + border + 1)));
                cout << paddedDemoImage << endl;
                imshow("image", paddedDemoImage * 255);
                waitKey(0);
            }
        }
    }

    // Crop out the original dimension from the padded output image
    Mat dilatedImage = paddedDemoImage(Range(border, border + height), Range(border, border + width));
    imshow("image", dilatedImage * 255);
    waitKey(0);

    Mat dilatedEllipseKernel;
    dilate(demoImage, dilatedEllipseKernel, element);
    cout << dilatedEllipseKernel << endl;

    imshow("image", dilatedEllipseKernel * 255);
    waitKey(0);

    return 0;
}
