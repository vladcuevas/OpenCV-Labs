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

  // Method1 - Specify width and height
  int resizeDownWidth = 300;
  int resizeDownHeight = 200;
  Mat resizedDown;
  resize(image, resizedDown, Size(resizeDownWidth, resizeDownHeight), INTER_LINEAR);

  // Mess up with the aspect ratio
  int resizeUpWidth = 600;
  int resizeUpHeight = 900;
  Mat resizedUp;
  resize(image, resizedUp, Size(resizeUpWidth, resizeUpHeight), INTER_LINEAR);

  icv.displayImage(resizedUp);
  icv.displayImage(resizedDown);  

  //Method2 - Specify scaling factor

  // Scaling Down the image 1.5 times by specifying both scaling factors
  double scaleUpX = 1.5;
  double scaleUpY = 1.5;

  // Scaling Down the image 0.6 times specifying a single scale factor.
  double scaleDown = 0.6;

  Mat scaledUp, scaledDown;

  resize(image, scaledDown, Size(), scaleDown, scaleDown, INTER_LINEAR);

  resize(image, scaledUp, Size(), scaleUpX, scaleUpY, INTER_LINEAR);

  imgPath = cm.GetImageDataPath("/images/results/scaledUp.png");
  imwrite(imgPath, scaledUp);
  imgPath = cm.GetImageDataPath("/images/results/scaledDown.png");
  imwrite(imgPath, scaledDown);

  icv.displayImage(scaledDown);
  icv.displayImage(scaledUp);

  cout << "\n";
  destroyAllWindows();
  return 0;
}