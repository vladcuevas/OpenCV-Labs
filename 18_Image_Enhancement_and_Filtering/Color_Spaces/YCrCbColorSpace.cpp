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

Mat imH, imS, imV, imhsv, imbgr;
vector<Mat> channels;

for (int i=0; i < 7; i++) {
    imH = Mat::ones(Size(50,50),CV_8U) * (i*30);
    imS = Mat::ones(Size(50,50),CV_8U) * 128;
    imV = Mat::ones(Size(50,50),CV_8U) * 128;
    
    channels = {imH, imS, imV};
    
    merge(channels, imhsv);
    
    cvtColor(imhsv, imbgr, COLOR_HSV2BGR);

}

Mat ycbImage;

cvtColor(bgr, ycbImage, COLOR_BGR2YCrCb);
split(ycbImage,channels);

imshow("Blue Channel", channels[0]);
waitKey(0);

imshow("Gren Channel", channels[1]);
waitKey(0);

imshow("Red Channel", channels[2]);
waitKey(0);

return 0;
}
