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

#define channelNumbers 3

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

  // Io=I+β
  // In the code below, we will apply the above mentioned formulas to get brightness enhanced images.
  // We will increase the brightness by 50 intensity levels. (Note that there are 255 intensity levels in a image)

  int brightnessOffset = 50;

  // Add the offset for increasing brightness
  Mat brightHigh = image;
  Mat brightHighChannels[channelNumbers];
  split(brightHigh, brightHighChannels);

  for (int i=0; i < channelNumbers; i++){
    add(brightHighChannels[i],brightnessOffset,brightHighChannels[i]);
  }

  merge(brightHighChannels,channelNumbers,brightHigh);
  imwrite(cm.GetImageDataPath("/images/results/highBrightness.png"),brightHigh);

  icv.displayImage(brightHigh);

  double minVal, maxVal;
  cout << "Original Image Datatype : " << icv.type2str(image.type()) << endl;
  cout << "Brightness Image Datatype : " << icv.type2str(brightHigh.type()) << endl;

  minMaxLoc(image, &minVal, &maxVal);
  cout << "Original Image Highest Pixel Intensity : " << maxVal << endl;
  minMaxLoc(brightHigh, &minVal, &maxVal);
  cout << "Brightness Image Highest Pixel Intensity : " << maxVal << endl;

  cout << "\n";
  destroyAllWindows();
  return 0;
}