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

  // Create a mask using coordinates

  // Create an empty image of same size as the original
  Mat mask1 = Mat::zeros(image.size(), image.type());
  icv.displayImage(mask1);

  mask1(Range(50,200),Range(170,320)).setTo(255);
  icv.displayImage(image);
  icv.displayImage(mask1);

  //Create a mask using pixel intensity or color

  //  * The red channel should have high intensity 
  //    ( keep the range of pixel values from 150 to 255 )
  //  * The other 2 channels should have low intensity 
  //    ( keep the range of pixel values in Blue and Green channels between 0 to 100)

  Mat mask2;
  inRange(image, Scalar(0,0,150), Scalar(100,100,255), mask2);
  icv.displayImage(image);
  icv.displayImage(mask2);

  cout << "\n";
  destroyAllWindows();
  return 0;
}