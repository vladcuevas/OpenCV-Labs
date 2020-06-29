#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <iostream> // std::cout
#include <string>   // std::string, std::to_string

#include <stdio.h> /* defines FILENAME_MAX */
// #define WINDOWS  /* uncomment this line to use it for windows.*/

#include <direct.h>
#define GetCurrentDir _getcwd

using namespace cv;
using namespace std;

std::string GetCurrentWorkingDir(void)
{
  char buff[FILENAME_MAX];
  _getcwd(buff, FILENAME_MAX);
  std::string current_working_dir(buff);
  return current_working_dir;
}

string type2str(int type)
{
  string r;

  uchar depth = type & CV_MAT_DEPTH_MASK;
  uchar chans = 1 + (type >> CV_CN_SHIFT);

  //U = Unsigned, S = Signed, F = Floating point
  switch (depth)
  {
  case CV_8U:
    r = "8U";
    break;
  case CV_8S:
    r = "8S";
    break;
  case CV_16U:
    r = "16U";
    break;
  case CV_16S:
    r = "16S";
    break;
  case CV_32S:
    r = "32S";
    break;
  case CV_32F:
    r = "32F";
    break;
  case CV_64F:
    r = "64F";
    break; //64 bit floating point number
  default:
    r = "User";
    break;
  }

  r += "C";
  r += (chans + '0');

  return r;
}

int main()
{
  string DATA_DIR = GetCurrentWorkingDir();

  string inputFileName = DATA_DIR + "\\number_zero.jpg";

  std::cout << "Read image " << inputFileName << " in Grayscale format\n";

  // Read image in GrayScale mode
  Mat testImage = imread(inputFileName, 0);

  cout << "\n";
  cout << testImage;
  cout << "\n\n";

  cout << "Data type = " << type2str(testImage.type()) << endl;
  cout << "\n";
  cout << "Image Dimensions = " << testImage.size();
  cout << "\n";
  cout << "Python returns in height x width, C++ in width x height\n";

  cout << "Read (y) row 0, (x) column 0"
       << "\n";
  cout << "Result is " << (int)testImage.at<uchar>(0, 0) << "\n";

  testImage.at<uchar>(0, 0) = 200;

  cout << "\n";
  cout << testImage;
  cout << "\n\n";

  //Select region of an image
  Mat test_roi = testImage(Range(0, 2), Range(0, 4));
  cout << "Original Matrix\n"
       << testImage << endl
       << endl;
  cout << "Selected Region\n"
       << test_roi;

  cout << "\n\n";

  //set region of an image
  testImage(Range(0, 2), Range(0, 4)).setTo(111);
  cout << "Modified Matrix\n"
       << testImage;

  cout << "\n";
  cout << "\n";

  // Read an image
  string imagePath = DATA_DIR + "\\boy.jpg";
  cout << "Reading " + imagePath + "\n";
  Mat boy = imread(imagePath);
  // Display the image using imshow
  imshow("Boy", boy);
  // Wait for user to press a key
  waitKey(0);
  // Destroy the window
  destroyAllWindows();

  cout << "\n";
  return 0;
}