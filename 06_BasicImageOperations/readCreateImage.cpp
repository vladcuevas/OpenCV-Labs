// Include libraries
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <iostream> // std::cout
#include <string>   // std::string, std::to_string

#include <stdio.h> /* defines FILENAME_MAX */
// #define WINDOWS  /* uncomment this line to use it for windows.*/

#include <direct.h>
#define GetCurrentDir _getcwd

using namespace cv;
using namespace std;

void displayImage(Mat image, int delay = 0)
{
    namedWindow("GenericWindow", WINDOW_AUTOSIZE);
    imshow("GenericWindow", image);
    waitKey(delay);
}

vector<int> setCompressionParameters(int jpg_quality)
{
  vector<int> compression_params;
  compression_params.push_back(IMWRITE_JPEG_QUALITY);
  compression_params.push_back(jpg_quality);
  // compression_params.push_back(IMWRITE_JPEG_PROGRESSIVE);
  // compression_params.push_back(1);
  // compression_params.push_back(IMWRITE_JPEG_OPTIMIZE);
  // compression_params.push_back(1);
  // compression_params.push_back(IMWRITE_JPEG_LUMA_QUALITY);
  // compression_params.push_back(30);

  return compression_params;
}

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
  string DATA_PATH = GetCurrentWorkingDir();

  //Create new Images

  cout << DATA_PATH << endl;

  string imgPath = DATA_PATH+"/images/boy.jpg";

  cout << imgPath << endl;

  // Read image
  Mat image = imread(imgPath);

  cout << "image size = " << image.size() << endl;
  cout << "image channels = " << image.channels();

  displayImage(image);

  // Create copy of an Image
  // Create a new image by copying the already present image using the clone operation
  Mat imageCopy = image.clone();
  
  // Create a empty matrix
  // Let us create an empty matrix with size (100,200).
  Mat emptyMatrix = Mat(100,200,CV_8UC3, Scalar(0,0,0));
  displayImage(emptyMatrix);

  // Let's fill it with white pixels

  emptyMatrix.setTo(Scalar(255,255,255));
  displayImage(emptyMatrix);


  // Create a empty matrix of the same size as original image
  // Let us create a matrix with the same size and data type as the original image and fill it with 100.

  Mat emptyOriginal = Mat(emptyMatrix.size(), emptyMatrix.type(), Scalar(100,100,100));
  displayImage(emptyOriginal);

  cout << "\n";
  destroyAllWindows();
  return 0;
}