// Include libraries
#include <iostream>
// #include "includeLibraries.h"
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <time.h>
#include "dataPath.hpp"
#include <filesystem>
#include <string>
#include <format>

using namespace std;
using namespace cv;

namespace fs = std::filesystem;

int main(int argc, char *argv[])
{
    // This program can be executed as an example without parameters
    // also, can be called with two parameters,
    // the first parameter is the image path
    // the second parameter is 0 (to run without showing the images, aka silent mode)
    // or 1 (to run showing the images)
    // by default it will show the images, because this is an example

    std::string img_path = DATA_PATH + "images/girl.jpg";

    int isImShow = 1;
    fs::path fs_path;
    fs::path parentStem;

    if (argc > 1) {
        img_path = argv[1];
        fs_path = fs::path{img_path};
        parentStem = fs_path.parent_path()/fs_path.stem();

        try
        {
            isImShow = stoul(argv[2],nullptr,0);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            isImShow = 0;
        }
    }

    if (fs::exists(fs_path)) {
        // Read image
        Mat img = imread(img_path);

        if (isImShow == 1) {
            imshow("Original Image", img);
            waitKey(0);
        }

        // Specify scaling factor
        float saturationScale = 0.01f;

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
        
        if (isImShow == 1) {
            imshow("Desaturated Image", imSat);
            waitKey(0);
        }

        if (argc > 1) {
            std::string newPath = std::format(
                "{}_gray{}", 
                parentStem.generic_string(),
                fs_path.extension().generic_string()
            );

            cout << newPath << endl;
            imwrite(newPath, imSat);
        }
    }
    else {
        cout << "The provided path is not valid!";
    }

    return 0;
}
