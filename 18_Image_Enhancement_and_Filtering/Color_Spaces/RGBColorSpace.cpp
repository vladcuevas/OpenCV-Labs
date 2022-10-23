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

Mat bgrChannels[3];
split(bgr,bgrChannels);

imshow("Blue Channel", bgrChannels[0]);
waitKey(0);

imshow("Gren Channel", bgrChannels[1]);
waitKey(0);

imshow("Red Channel", bgrChannels[2]);
waitKey(0);

return 0;
}
