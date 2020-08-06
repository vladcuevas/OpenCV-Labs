// Include libraries
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <iostream> // std::cout
#include <string>   // std::string, std::to_string

#include <stdio.h> /* defines FILENAME_MAX */
// #define WINDOWS  /* uncomment this line to use it for windows.*/

#include <direct.h>

#include "image_cv.h"
#define GetCurrentDir _getcwd

using namespace cv;
using namespace std;

void image_cv::displayImage(Mat image, int delay)
{
    namedWindow("GenericWindow", WINDOW_AUTOSIZE);
    imshow("GenericWindow", image);
    waitKey(delay);
}

Mat image_cv::cropImage(Mat image, int x1, int x2, int y1, int y2)
{
    // Crop out a rectangle
    // slicing
    return image(Range(y1, y2), Range(x1, x2));
}

vector<int> image_cv::setCompressionParameters(int jpg_quality)
{
    vector<int> compression_params;
    compression_params.push_back(IMWRITE_JPEG_QUALITY);
    compression_params.push_back(jpg_quality);
    // compression_params.push_back(IMWRITE_JPEG_PROGRESSIVE);
    // compression_params.push_back(1);
    // compression_params.push_back(IMWRITE_JPEG_OPTIMIZE);
    // compression_params.push_back(1);
    // compression_params.push_back(IMWRITE_JPEG_LUMA_QUALITY);
    // compression_params.push_back(30);

    return compression_params;
}

string image_cv::type2str(int type)
{
    string r;

    uchar depth = type & CV_MAT_DEPTH_MASK;
    uchar chans = 1 + (type >> CV_CN_SHIFT);

    //U = Unsigned, S = Signed, F = Floating point
    switch (depth)
    {
    case CV_8U:
        r = "8U";
        break;
    case CV_8S:
        r = "8S";
        break;
    case CV_16U:
        r = "16U";
        break;
    case CV_16S:
        r = "16S";
        break;
    case CV_32S:
        r = "32S";
        break;
    case CV_32F:
        r = "32F";
        break;
    case CV_64F:
        r = "64F";
        break; //64 bit floating point number
    default:
        r = "User";
        break;
    }

    r += "C";
    r += (chans + '0');

    return r;
}