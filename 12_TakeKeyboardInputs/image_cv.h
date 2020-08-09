// Include libraries
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <iostream> // std::cout
#include <string>   // std::string, std::to_string

#include <stdio.h> /* defines FILENAME_MAX */
// #define WINDOWS  /* uncomment this line to use it for windows.*/

#include <direct.h>

using namespace cv;
using namespace std;

class image_cv {
public:

  void displayImage(Mat image, int delay = 0);

  Mat cropImage(Mat image, int x1, int x2, int y1, int y2);

  vector<int> setCompressionParameters(int jpg_quality);

  string type2str(int type);

};