#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <iostream> // std::cout
#include <string>   // std::string, std::to_string

using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{
  if (argc != 2)
    std::cout << "Usage is grayImage.exe <image_filename.jpg>";
  else
  {
    
    string inputFileName = argv[1];

    std::cout << "Image to be converted to gray scale is " << inputFileName;

    // Read image in GrayScale mode
    Mat image = imread(inputFileName, 0);

    size_t lastindex = inputFileName.find_last_of(".");
    string rawname = inputFileName.substr(0, lastindex);

    // Save grayscale image
    imwrite(rawname + "Gray.jpg", image);
  }

  return 0;
}