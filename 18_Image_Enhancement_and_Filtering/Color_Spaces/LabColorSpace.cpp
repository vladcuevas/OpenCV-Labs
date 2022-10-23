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
vector<Mat> channels;

imshow("Image",bgr);
waitKey(0);

Mat labImage;
cvtColor(bgr, labImage, COLOR_BGR2Lab);

split(labImage,channels);

imshow("L Channel", channels[0]);
waitKey(0);

imshow("A Channel", channels[1]);
waitKey(0);

imshow("B Channel", channels[2]);
waitKey(0);

return 0;
}
