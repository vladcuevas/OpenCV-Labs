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

  // Read image
  Mat faceImage  = imread(imgPath);
  faceImage.convertTo(faceImage, CV_32FC3);
  faceImage = faceImage/255.0;

  icv.displayImage(faceImage);

  // Load the Sunglass image with Alpha channel
  // (http://pluspng.com/sunglass-png-1104.html)
  string glassimagePath = cm.GetImageDataPath("/images/sunglass.png");

  // Read the image
  Mat glassPNG = imread(glassimagePath,-1);
  glassPNG.convertTo(glassPNG,CV_32F);
  glassPNG = glassPNG/255.0;
  icv.displayImage(glassPNG);
  // Resize the image to fit over the eye region
  resize(glassPNG,glassPNG, Size(), 0.5, 0.5);
  icv.displayImage(glassPNG);

  cout << "Image Dimension = " << glassPNG.size() << endl;
  cout << "Number of channels = " << glassPNG.channels();

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
  icv.displayImage(glassMask1*255);

  // ## Using Naive Replace
  // The easiest way that might have come to your mind 
  // would be to just replace the eye region with that of the sunglass. Let us give it a try.

  // Top left corner of the glasses
  int topLeftRow = 130;
  int topLeftCol = 130;

  int bottomRightRow = topLeftRow + glassHeight;
  int bottomRightCol = topLeftCol + glassWidth;

  // Make a copy
  Mat faceWithGlassesNaive = faceImage.clone();
  Mat roiFace =  faceWithGlassesNaive(
    Range(
        topLeftRow,
        bottomRightRow
      ),
      Range(
        topLeftCol,bottomRightCol
      )
  );
  // Replace the eye region with the sunglass image
  glassBGR.copyTo(roiFace);

  icv.displayImage(faceWithGlassesNaive);

  // You can see that the output is not even close. 
  // This is because the BGR image is opaque and will 
  // either have a black or white rectangle around the sunglass.
  // We need to use a mask along with the sunglass image 
  // in order to get the desired output. 
  // Let us see how it can be done with very simple steps 
  // using the tools we have learned till now.


  // Using Arithmetic Operations and Alpha Mask

  // In order to put the sunglass on top of the eye region, we need to follow these steps:

  //  Create a binary mask with 3-channels using the single channel mask.
  //  Extract the eye region from the face image
  //  Multiply the Mask with the sunglass to get the masked sunglass
  //  Multiply the negative of Mask with the eye region to create a hole in the eye region for the sunglass to be placed.
  //  Add the masked sunglass and eye regions to get the combined eye region with the sunglass.
  //  Replace the eye region in the original image with that of the output we got in the previous step. This is the final output

  // Make the dimensions of the mask same as the input image.
  // Since Face Image is a 3-channel image, we create a 3 channel image for the mask
  Mat glassMask;
  Mat glassMaskChannels[] = {glassMask1,glassMask1,glassMask1};
  merge(glassMaskChannels,3,glassMask);

  // Make a copy
  Mat faceWithGlassesArithmetic = faceImage.clone();

  // Get the eye region from the face image
  Mat eyeROI = faceWithGlassesArithmetic(Range(topLeftRow,bottomRightRow),Range(topLeftCol,bottomRightCol));

  Mat eyeROIChannels[3];
  split(eyeROI,eyeROIChannels);
  Mat maskedEyeChannels[3];
  Mat maskedEye;

  for (int i = 0; i < 3; i++)
  {
      // Use the mask to create the masked eye region
      multiply(eyeROIChannels[i], (1-glassMaskChannels[i]/2), maskedEyeChannels[i]);
  }

  merge(maskedEyeChannels,3,maskedEye);

  Mat maskedGlass;
  // Use the mask to create the masked sunglass region
  multiply(glassBGR, glassMask, maskedGlass);

  Mat eyeRoiFinal;
  // Combine the Sunglass in the Eye Region to get the augmented image
  add(maskedEye, maskedGlass, eyeRoiFinal);  

  icv.displayImage(maskedEye);
  icv.displayImage(maskedGlass);
  icv.displayImage(eyeRoiFinal);

  // Replace the eye ROI with the output from the previous section
  eyeRoiFinal.copyTo(eyeROI);

  icv.displayImage(faceImage);
  icv.displayImage(faceWithGlassesArithmetic);

  cout << "\n";
  destroyAllWindows();
  return 0;
}