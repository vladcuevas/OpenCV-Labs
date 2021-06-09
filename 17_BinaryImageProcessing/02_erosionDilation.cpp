#include <iostream>
#include "dataPath.hpp"

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

int main(){
string imageName = DATA_PATH + "images/dilation_example.jpg";

// Read the input image
Mat image = imread(imageName, IMREAD_COLOR);

imshow("image",image);
waitKey(0);

int kSize = 7;
Mat kernel1 = getStructuringElement(
  cv::MORPH_ELLIPSE,
  cv::Size(kSize, kSize)
);

imshow("image",image);
waitKey(0);

Mat imageDilated;
dilate(image, imageDilated, kernel1);
cout << "dilate(image, imageDilated, kernel1);" << endl;

imshow("image",imageDilated);
waitKey(0);

kSize = 3;
Mat kernel2 = getStructuringElement(cv::MORPH_ELLIPSE,
       cv::Size(kSize, kSize));

imshow("image",kernel2*255);
waitKey(0);

Mat imageDilated1, imageDilated2;
dilate(image, imageDilated1, kernel2, Point(-1,-1), 1);
dilate(image, imageDilated2, kernel2, Point(-1,-1), 2);
cout << "dilate(image, imageDilated2, kernel2, Point(-1,-1), 2);" << endl;
cout << "dilate(image, imageDilated2, kernel2, Point(-1,-1), 2);" << endl;

imshow("image",imageDilated1);
waitKey(0);
imshow("image",imageDilated2);
waitKey(0);

imageName = DATA_PATH + "images/erosion_example.jpg";

// Read the input image
image = imread(imageName, IMREAD_COLOR);

imshow("image",image);
waitKey(0);

Mat imageEroded;
// First parameter is the original image, second is the eroded image  
erode(image, imageEroded, kernel1);
cout << "erode(image, imageEroded, kernel1);" << endl;

imshow("image",imageEroded);
waitKey(0);

return 0;
}
