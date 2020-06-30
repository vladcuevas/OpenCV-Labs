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

  string inputFileName = DATA_PATH + "\\number_zero.jpg";

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
  testImage(Range(0, 2), Range(0, 4)).setTo(222);
  cout << "Modified Matrix\n"
       << testImage;

  size_t lastindex = inputFileName.find_last_of(".");
  string rawname = inputFileName.substr(0, lastindex);

  //extension defines the type
  imwrite(rawname + "_changed.jpg", testImage, setCompressionParameters(90));

  cout << "\n";
  cout << "\n";

  // Read an image
  string imagePath = DATA_PATH + "\\boy.jpg";
  cout << "Reading " + imagePath + "\n";
  Mat boy = imread(imagePath);
  namedWindow("Boy", WINDOW_AUTOSIZE);
  // Display the image using imshow
  imshow("Boy", boy);
  // Wait for user to press a key
  waitKey(0);
  // Destroy the window

  cout << "image size = " << boy.size() << endl;
  cout << "image channels = " << boy.channels();
  //3 channels mean that image is RGB
  //4 channels mean that image is Alpha
  //Blue channel is indexed first,
  //followed by the Green Channel and finally the Red Channel

  // Show the channels
  Mat imgChannels[3];
  split(boy, imgChannels);
  cout << "\n";

  cout << "blue channel\n";
  imshow("Boy", imgChannels[0]);
  waitKey(250);
  cout << "green channel\n";
  imshow("Boy", imgChannels[1]);
  waitKey(250);
  cout << "red channel\n";
  imshow("Boy", imgChannels[2]);
  waitKey(250);
  imshow("Boy", boy);
  waitKey(250);
  destroyWindow("Boy");

  testImage = imread(inputFileName, 1);

  //Manipulating Color Pixels
  namedWindow("Zero", WINDOW_NORMAL);
  resizeWindow("Zero", 600, 600);
  imshow("Zero", testImage);
  waitKey(250);

  cout << "\n";
  cout << testImage.at<Vec3b>(0, 0);

  testImage.at<Vec3b>(0, 0) = Vec3b(0, 255, 255);
  imshow("Zero", testImage);
  waitKey(500);
  testImage.at<Vec3b>(1, 1) = Vec3b(255, 255, 0);
  imshow("Zero", testImage);
  waitKey(500);
  testImage.at<Vec3b>(2, 2) = Vec3b(255, 0, 255);
  imshow("Zero", testImage);
  waitKey(500);

  testImage = imread(inputFileName, 1);
  testImage(Range(0, 3), Range(0, 3)).setTo(Scalar(255, 0, 0));
  imshow("Zero", testImage);
  waitKey(500);
  testImage(Range(3, 6), Range(0, 3)).setTo(Scalar(0, 255, 0));
  imshow("Zero", testImage);
  waitKey(500);
  testImage(Range(6, 9), Range(0, 3)).setTo(Scalar(0, 0, 255));
  imshow("Zero", testImage);
  waitKey(500);
  destroyWindow("Zero");

  // Images with Alpha Channel
  // In images with an alpha channel, each pixel not only has a color value, but also has a numerical transparency value ( between 0 to 255) that defines what will happen when the pixel is placed over another pixel.
  // There are 4 channels, i.e. 3 color channels and 1 alpha channel which indicates the transparency.

  imagePath = DATA_PATH + "/panther.png";

  // Read the image
  // Note that we are passing flag = -1 while reading the image ( it will read the image as is)
  Mat imgPNG = imread(imagePath, -1);
  cout << "image size = " << imgPNG.size() << endl;
  cout << "number of channels = " << imgPNG.channels() << endl;

  Mat imgBGR;
  Mat imgPNGChannels[4];
  split(imgPNG, imgPNGChannels);

  merge(imgPNGChannels, 3, imgBGR);

  Mat imgMask = imgPNGChannels[3];

  namedWindow("Panther", WINDOW_AUTOSIZE);
  imshow("Panther", imgBGR);
  waitKey(500);
  imshow("Panther", imgMask);
  waitKey(500);

  cout << "\n";
  destroyAllWindows();
  return 0;
}