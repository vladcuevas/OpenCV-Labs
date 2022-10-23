// Include libraries
#include <iostream>
// #include "includeLibraries.h"
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <time.h>
#include "dataPath.hpp"

using namespace std;
using namespace cv;

std::vector<std::string> tokenize(string s, string del = ",")
{
    int start, end = -1*del.size();
    std::vector<std::string> tokens;
    do {
        start = end + del.size();
        end = s.find(del, start);
        tokens.push_back(s.substr(start, end - start));
    } while (end != -1);

    return tokens;
}

int main(int argc, char *argv[])
{
    std::string img_path = DATA_PATH + "images/girl.jpg";

    if (argc > 1) {
        img_path = argv[1];
    }

    // Read image
    Mat img = imread(img_path);

    imshow("Original Image", img);
    waitKey(0);

    // Specify scaling factor
    float saturationScale = 0.01;

    // Convert to HSV color space
    Mat hsvImage;
    cv::cvtColor(img, hsvImage, COLOR_BGR2HSV);

    // Convert to float32
    hsvImage.convertTo(hsvImage, CV_32F);

    vector<Mat> channels(3);

    // Split the channels
    split(hsvImage, channels);

    // Multiply S channel by scaling factor
    channels[1] = channels[1] * saturationScale;

    // Clipping operation performed to limit pixel values
    // between 0 and 255
    min(channels[1], 255, channels[1]);
    max(channels[1], 0, channels[1]);

    // Merge the channels
    merge(channels, hsvImage);

    // Convert back from float32
    hsvImage.convertTo(hsvImage, CV_8UC3);

    Mat imSat;
    // Convert to BGR color space
    cv::cvtColor(hsvImage, imSat, COLOR_HSV2BGR);

    imshow("Desaturated Image", imSat);
    waitKey(0);

    if (argc > 1) {
        std::vector<std::string> tokens = tokenize(img_path, ".");
        std::string newPath = tokens[0] + "_gray." + tokens[1];
        cout << newPath << endl;
        imwrite(newPath, imSat);
    }

    return 0;
}
