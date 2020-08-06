// Include libraries
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <iostream> // std::cout
#include <string>   // std::string, std::to_string
#include <stdio.h> /* defines FILENAME_MAX */
// #define WINDOWS  /* uncomment this line to use it for windows.*/

#include "commons.h"
#include "image_cv.h"

using namespace cv;
using namespace std;

int main()
{
  commons cm;
  image_cv icv;

  string imgPath = cm.GetImageDataPath("/images/boy.jpg");

  // Read image
  Mat image = imread(imgPath);

  icv.displayImage(image);

  double scalingFactor = 1/255.0;
  double shift = 0;

  //Converting from unsigned char to float(32bit)
  image.convertTo(image, CV_32FC3, scalingFactor, shift);

  icv.displayImage(image);

  //Converting from float to unsigned char
  image.convertTo(image, CV_8UC3, 1.0/scalingFactor, shift);

  icv.displayImage(image);

  cout << "\n";
  destroyAllWindows();
  return 0;
}