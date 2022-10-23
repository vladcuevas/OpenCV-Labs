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

int main(){
// Read image
Mat bgr = imread(DATA_PATH + "images/capsicum.jpg");

imshow("Image",bgr);
waitKey(0);

Mat hsvImage;
cvtColor(bgr, hsvImage, COLOR_BGR2HSV);

Mat hsvChannels[3];
split(hsvImage,hsvChannels);

imshow("Blue Channel", hsvChannels[0]);
waitKey(0);

imshow("Gren Channel", hsvChannels[1]);
waitKey(0);

imshow("Red Channel", hsvChannels[2]);
waitKey(0);

return 0;
}
