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

  string imageName = cm.GetImageDataPath("/images/boy.jpg");
  
  // Load the image
  Mat image;
  image = imread(imageName, IMREAD_COLOR);

  icv.displayImage(image);

  // Draw a line
  Mat imageLine = image.clone();

  // The line starts from (200,80) and ends at (280,80)
  // The color of the line is GREEN (Recall that OpenCV uses BGR format)
  // Thickness of line is 3px
  // Linetype is LINE_AA

  line(imageLine, Point(200, 80), Point(280, 80), Scalar(0, 255, 0), 3, LINE_AA);

  icv.displayImage(imageLine);
  
  //Draw a Circle
  Mat imageCircle = image.clone();

  circle(imageCircle, Point(250, 125), 100, Scalar(0, 0, 255), 5, LINE_AA);

  icv.displayImage(imageCircle);

  // Draw a filled circle
  Mat imageFilledCircle = image.clone();

  circle(imageFilledCircle, Point(250, 125), 100, Scalar(0, 0, 255), -1, LINE_AA);

  icv.displayImage(imageFilledCircle);  

  // Draw an ellipse
  // Note: Ellipse Centers and Axis lengths must be integers
  Mat imageEllipse = image.clone();

  ellipse(imageEllipse, Point(250, 125), Point(100, 50), 0, 0, 360, 
          Scalar(255, 0, 0), 3, LINE_AA);

  ellipse(imageEllipse, Point(250, 125), Point(100, 50), 90, 0, 360,
          Scalar(0, 0, 255), 3, LINE_AA);

  icv.displayImage(imageEllipse);

  // Draw an ellipse
  // Note: Ellipse Centers and Axis lengths must be integers
  imageEllipse = image.clone();

  // Incomplete/Open ellipse
  ellipse(imageEllipse, Point(250, 125), Point(100, 50), 0, 180, 360, 
          Scalar(255, 0, 0), 3, LINE_AA);

  // Filled ellipse
  ellipse(imageEllipse, Point(250, 125), Point(100, 50), 0, 0, 180, 
          Scalar(0, 0, 255), -2, LINE_AA);

  icv.displayImage(imageEllipse);  

  // Draw a rectangle (thickness is a positive integer)
  Mat imageRectangle = image.clone();
  rectangle(imageRectangle, Point(170, 50), Point(300, 200), 
            Scalar(255, 0, 255), 5, LINE_8);

  icv.displayImage(imageRectangle);  

  // Put text on image
  Mat imageText = image.clone();
  string textStr = "I am studying";
  double fontScale = 1.5;
  int fontFace = FONT_HERSHEY_COMPLEX;
  Scalar fontColor = Scalar(250, 10, 10);
  int fontThickness = 2;

  putText(
    imageText, 
    textStr, Point(20, 350), 
    fontFace, 
    fontScale, 
    fontColor, 
    fontThickness, 
    LINE_AA
  );

  icv.displayImage(imageText);

  int pixelHeight = 20;

  // Calculate the fontScale
  fontScale = getFontScaleFromHeight(fontFace, pixelHeight, fontThickness);
  cout << "fontScale = " << fontScale;

  Mat imageTextFontScale;
  imageTextFontScale = image.clone();
  putText(imageTextFontScale, textStr, Point(20, 350), fontFace, fontScale, fontColor, fontThickness, LINE_AA);

  icv.displayImage(imageTextFontScale);

  Mat imageGetTextSize;
  imageGetTextSize = image.clone();
  int imageHeight = imageGetTextSize.rows;
  int imageWidth = imageGetTextSize.cols;

  // Get the text box height and width and also the baseLine
  int baseLine = 0;
  Size textSize = getTextSize(textStr,fontFace,fontScale,fontThickness, &baseLine);

  int textWidth = textSize.width;
  int textHeight = textSize.height;

  cout << "TextWidth = " << textWidth << ", TextHeight = " << textHeight << ", baseLine = " << baseLine;

  // Get the coordinates of text box bottom left corner
  // The xccordinate will be such that the text is centered
  int xcoordinate = (imageWidth - textWidth)/2;
  // The y coordinate will be such that the entire box is just 10 pixels above the bottom of image
  int ycoordinate = (imageHeight - baseLine - 10);

  cout << "TextBox Bottom Left = (" << xcoordinate << "," << ycoordinate << ")";

  // Draw the Canvas using a filled rectangle
  Scalar canvasColor = Scalar(255, 255, 255);
  Point canvasBottomLeft (xcoordinate,ycoordinate+baseLine);
  Point canvasTopRight (xcoordinate+textWidth, ycoordinate-textHeight);

  rectangle(imageGetTextSize, canvasBottomLeft, canvasTopRight, canvasColor, -1);

  cout << "Canvas Bottom Left = " << canvasBottomLeft << ", Top Right = " << canvasTopRight;

  // Now draw the baseline ( just for reference )
  int lineThickness = 2;
  Point lineLeft (xcoordinate, ycoordinate);
  Point lineRight (xcoordinate+textWidth, ycoordinate);
  Scalar lineColor = Scalar(0,255,0);

  line(imageGetTextSize, lineLeft, lineRight, lineColor, lineThickness, LINE_AA);

  // Finally Draw the text
  putText(imageGetTextSize, textStr, Point(xcoordinate,ycoordinate), fontFace, fontScale, 
          fontColor, fontThickness, LINE_AA);  
  
  icv.displayImage(imageGetTextSize);

  // DESTROY ALL WINDOWS
  cout << "\n";
  destroyAllWindows();
  return 0;
}