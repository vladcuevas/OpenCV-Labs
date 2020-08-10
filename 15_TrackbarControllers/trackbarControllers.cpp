// Include libraries
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <vector>
#include <iostream> // std::cout
#include <string>   // std::string, std::to_string
#include <stdio.h> /* defines FILENAME_MAX */
#include <direct.h>
// #define WINDOWS  /* uncomment this line to use it for windows.*/

#define GetCurrentDir _getcwd
#define channelNumbers 3

using namespace cv;
using namespace std;

int maxScaleUp = 100;
int scaleFactor = 1;
int scaleType = 0;
int maxType = 1;
Mat im;

string windowName = "Resize Image";
string trackbarValue = "Scale";
string trackbarType = "Type: \n 0: Scale Up \n 1: Scale Down";

void scaleImage(int, void*);

std::string GetCurrentWorkingDir(void)
{
    char buff[FILENAME_MAX];
    _getcwd(buff, FILENAME_MAX);
    std::string current_working_dir(buff);
    return current_working_dir;
}

string DATA_PATH = GetCurrentWorkingDir();

// Callback functions
void scaleImage(int, void*) {

    // Get the Scale factor from the trackbar
    double scaleFactorDouble = 1 + scaleFactor/100.0;

    if (scaleType == 1) {
      scaleFactorDouble = 1 - scaleFactor/100.0;
    }
    // cout << scaleFactorDouble << endl;
    // cout << scaleType << endl;

    if (scaleFactorDouble == 0) {
        scaleFactorDouble = 1;
    }
    cout << scaleFactorDouble << endl;

    Mat scaledImage;

    // Resize the image
    resize(im, scaledImage, Size(), scaleFactorDouble, scaleFactorDouble, INTER_LINEAR);
    imshow(windowName, scaledImage);
}

int main() {
    // load an image
    string imgPath = DATA_PATH+"/images/truth.png";
    im = imread(imgPath);
    // Create a window to display results
    namedWindow(windowName, WINDOW_AUTOSIZE);

    // Create Trackbars and associate a callback function
    createTrackbar(trackbarValue, windowName, &scaleFactor, maxScaleUp, scaleImage);
    createTrackbar(trackbarType, windowName, &scaleType, maxType, scaleImage);

    scaleImage(25, 0);

    while (true) {
        int c;
        c = waitKey(20);
        if (static_cast<char>(c) == 27)
            break;
    }

    return 0;
}