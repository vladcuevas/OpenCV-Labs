#include <iostream>
#include "dataPath.hpp"

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
using namespace std;
using namespace cv;

int main(){
// Read image as grayscale
Mat img = imread(DATA_PATH+ "images/truth.png", IMREAD_GRAYSCALE);

imshow("image",img);
waitKey(0);

// Threshold Image
Mat imThresh;
threshold(img, imThresh, 127, 255, THRESH_BINARY);

// Find connected components
Mat imLabels;
int nComponents = connectedComponents(imThresh,imLabels);

Mat imLabelsCopy = imLabels.clone();

// First let's find the min and max values in imLabels
Point minLoc, maxLoc;
double min, max;

// The following line finds the min and max pixel values
// and their locations in an image.
minMaxLoc(imLabels, &min, &max, &minLoc, &maxLoc);

// Normalize the image so the min value is 0 and max value is 255.
imLabels = 255 * (imLabels - min) / (max - min);

// Convert image to 8-bits
imLabels.convertTo(imLabels, CV_8U);

imshow("image",imLabels);
waitKey(0);
imLabels = imLabelsCopy.clone();
// Display the labels
cout << "Number of components = " << nComponents;

for (int i=0; i < 6; i++){
	imshow("image",imLabels==i);
	waitKey(0);
}

// Make a copy of the image
imLabels = imLabelsCopy.clone();

// First let's find the min and max values in imLabels
// The following line finds the min and max pixel values
// and their locations in an image.
double minValue,maxValue;
minMaxLoc(imLabels, &minValue, &maxValue, &minLoc, &maxLoc);

// Normalize the image so the min value is 0 and max value is 255.
imLabels = 255 * (imLabels - minValue) / (maxValue - minValue);

// Convert image to 8-bits
imLabels.convertTo(imLabels, CV_8U);

// Apply a color map
Mat imColorMap;
applyColorMap(imLabels, imColorMap, COLORMAP_JET);

// Display colormapped labels
imshow("image",imColorMap);
waitKey(0);

return 0;
}
