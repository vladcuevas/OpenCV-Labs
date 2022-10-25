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

    std::string img_path = fs::current_path().generic_string() + DATA_PATH + "images/dark-flowers.jpg";

    int isImShow = 1;
    fs::path fs_path = fs::path{img_path};
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

        Mat imhsv;
        cvtColor(img, imhsv, COLOR_BGR2HSV);

        vector<Mat> imhsvChannels(3);
        split(imhsv,imhsvChannels);

        // Equalize histogram
        // Perform histogram equalization only on the V channel
        equalizeHist(imhsvChannels[2],imhsvChannels[2]);

        merge(imhsvChannels,imhsv);
        // Convert back to BGR format
        Mat imEq;
        cvtColor(imhsv,imEq, COLOR_HSV2BGR);
        
        if (isImShow == 1) {
            imshow("Original Image", img);
            waitKey(0);

            imshow("Equalized Image", imEq);
            waitKey(0);
        }

        if (argc > 1) {
            std::string newPath = std::format(
                "{}_equalized{}", 
                parentStem.generic_string(),
                fs_path.extension().generic_string()
            );

            cout << newPath << endl;
            imwrite(newPath, imEq);
        }
    }
    else {
        cout << "The provided path " << img_path << " is not valid!";
    }

    return 0;
}
