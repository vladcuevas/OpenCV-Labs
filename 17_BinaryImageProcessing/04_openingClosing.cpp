#include <iostream>
#include "dataPath.hpp"

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

int main(){

string imageName = DATA_PATH + "images/opening.png";
Mat image = imread(imageName, IMREAD_GRAYSCALE);
imshow("image",image);
waitKey(0);

// Specify Kernel Size
int kernelSize = 10;

// Create the kernel
Mat element = getStructuringElement(MORPH_ELLIPSE, Size(2*kernelSize+1, 2*kernelSize+1),
                                    Point(kernelSize, kernelSize));

imshow("image",255*element);
waitKey(0);

Mat imEroded;
// Perform Dilation
erode(image, imEroded, element, Point(-1,-1),1);

imshow("image",255*imEroded);
waitKey(0);

Mat imOpen;
dilate(imEroded, imOpen, element, Point(-1,-1),1);

imshow("image",255*imOpen);
waitKey(0);

// Get structuring element/kernel which will be used
// for opening operation
int openingSize = 3;

// Selecting a elliptical kernel
element = getStructuringElement(MORPH_ELLIPSE,Size(2 * openingSize + 1, 2 * openingSize + 1),
                                Point(openingSize, openingSize));

Mat imageMorphOpened;
morphologyEx(image, imageMorphOpened, MORPH_OPEN, element, Point(-1,-1),3);
imshow("image",imageMorphOpened*255);
waitKey(0);

imageName = DATA_PATH+"/images/closing.png";
// Image taken as input
image = imread(imageName, IMREAD_GRAYSCALE);

// Specify kernel size
kernelSize = 10;
// Create kernel
element = getStructuringElement(MORPH_ELLIPSE, Size(2*kernelSize+1, 2*kernelSize+1),
                                    Point(kernelSize, kernelSize));

Mat imDilated;
// Perform Dilation
dilate(image, imDilated, element);

imshow("image",imDilated);
waitKey(0);

Mat imClose;
// Perform erosion
erode(imDilated, imClose, element);

imshow("image",imClose);
waitKey(0);

// Create a structuring element
int closingSize = 10;
// Selecting a elliptical kernel and storing in Mat element
element = getStructuringElement(MORPH_ELLIPSE,Size(2 * closingSize + 1, 2 * closingSize + 1),
                                Point(closingSize, closingSize));

Mat imageMorphClosed;
morphologyEx(image, imageMorphClosed, MORPH_CLOSE, element);
imshow("image",imageMorphClosed);
waitKey(0);

return 0;
}
