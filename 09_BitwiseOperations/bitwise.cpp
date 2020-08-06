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

  string imgPath = cm.GetImageDataPath("/images/musk.jpg");
  
  // Load the Face Image
  Mat faceImage = imread(imgPath);

  // Make a copy
  Mat faceWithGlassesBitwise = faceImage.clone();

  // Load the Sunglass image with Alpha channel
  string glassimagePath = cm.GetImageDataPath("/images/sunglass.png");
  // Read the image
  Mat glassPNG = imread(glassimagePath,-1);
  // Resize the image to fit over the eye region
  resize(glassPNG,glassPNG, Size(), 0.5, 0.5);
  cout << "image Dimension = " << glassPNG.size() << endl;
  int glassHeight = glassPNG.size().height;
  int glassWidth = glassPNG.size().width;

  // Separate the Color and alpha channels
  Mat glassRGBAChannels[4];
  Mat glassRGBChannels[3];
  split(glassPNG, glassRGBAChannels);
  for (int i = 0; i < 3; i++){
      // Copy R,G,B channel from RGBA to RGB
      glassRGBChannels[i] = glassRGBAChannels[i];
  }
  Mat glassBGR, glassMask1;
  // Prepare BGR Image
  merge(glassRGBChannels,3,glassBGR);
  // Alpha channel is the 4th channel in RGBA Image
  glassMask1 = glassRGBAChannels[3];

  icv.displayImage(faceImage);
  icv.displayImage(glassBGR);
  icv.displayImage(glassMask1);

  // Top left corner of the glass
  int topLeftRow = 130;
  int topLeftCol = 130;

  int bottomRightRow = topLeftRow + glassHeight;
  int bottomRightCol = topLeftCol + glassWidth;

  // Get the eye region from the face image
  Mat eyeROI = faceWithGlassesBitwise(Range(topLeftRow,bottomRightRow),Range(topLeftCol,bottomRightCol));

  // Make the dimensions of the mask same as the input image.
  // Since Face Image is a 3-channel image, we create a 3 channel image for the mask
  Mat glassMask;
  Mat glassMaskChannels[] = {glassMask1,glassMask1,glassMask1};
  merge(glassMaskChannels,3,glassMask);

  // Use the mask to create the masked eye region
  Mat eye;
  Mat glassMaskNOT;
  bitwise_not(glassMask1, glassMaskNOT);

  Mat eyeChannels[3];
  Mat eyeROIChannels[3];
  Mat maskedGlass;
  Mat eyeRoiFinal;

  split(eyeROI,eyeROIChannels);

  for (int i = 0; i < 3; i++)
  {
      bitwise_and(eyeROIChannels[i], glassMaskNOT, eyeChannels[i]);
  }

  merge(eyeChannels,3,eye);

  Mat glassMaskNOTChannels[] = {glassMaskNOT,glassMaskNOT,glassMaskNOT};
  Mat glassMaskNOTMerged;
  merge(glassMaskNOTChannels,3,glassMaskNOTMerged);

  bitwise_and(eyeROI, glassMaskNOTMerged, eye);
  // Use the mask to create the masked sunglass region
  Mat sunglass;
  Mat sunglassChannels[3];
  Mat glassBGRChannels[3];

  split(glassBGR,glassBGRChannels);

  for (int i=0; i < 3; i++)
      bitwise_and(glassBGRChannels[i], glassMask1, sunglassChannels[i]);

  merge(sunglassChannels,3,sunglass);
  multiply(glassBGR, glassMask, maskedGlass);

  // Combine the Sunglass in the Eye Region to get the augmented image
  bitwise_or(eye, sunglass, eyeRoiFinal);

  icv.displayImage(eye);
  icv.displayImage(sunglass);
  icv.displayImage(eyeRoiFinal);  

  icv.displayImage(faceImage);
  icv.displayImage(faceWithGlassesBitwise);

  cout << "\n";
  destroyAllWindows();
  return 0;
}