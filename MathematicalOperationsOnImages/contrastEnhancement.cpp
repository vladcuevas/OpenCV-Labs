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

  // In the code below, we will apply the above 
  // mentioned formulas Io=αI to get contrast enhanced images.
  // We will increase the contrast by 30%.

  double contrastPercentage = 30.0;
  // Multiply with scaling factor to increase contrast
  Mat contrastHigh = image;

  // Convert contrastHigh to float
  contrastHigh.convertTo(contrastHigh, CV_64F);
  contrastHigh = contrastHigh * (1+contrastPercentage/100.0);
  imwrite(cm.GetImageDataPath("/images/results/highContrast.png"), contrastHigh);

  icv.displayImage(contrastHigh);

  cout << "\n";
  destroyAllWindows();
  return 0;
}