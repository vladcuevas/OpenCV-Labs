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

  // First let us create a copy of the original image 
  Mat copiedImage = image.clone();

  // Crop out a rectangle
  // x coordinates = 170 to 320
  // y coordinates = 40 to 200
  Mat copyRoi = icv.cropImage(image, 180, 320, 40,200);

  icv.displayImage(copyRoi);

  // Find height and width of the ROI
  int roiHeight = copyRoi.size().height;
  int roiWidth = copyRoi.size().width;

  // Copy to left of Face
  copyRoi.copyTo(copiedImage(Range(40,40+roiHeight),Range(10,10+roiWidth)));
  // Copy to right of Face
  copyRoi.copyTo(copiedImage(Range(40,40+roiHeight),Range(330,330+roiWidth)));

  icv.displayImage(copiedImage);

  cout << "\n";
  destroyAllWindows();
  return 0;
}