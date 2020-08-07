// Include libraries
#include "includeLibraries.h"
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <iostream> // std::cout
#include <string>   // std::string, std::to_string
#include <stdio.h> /* defines FILENAME_MAX */
// #define WINDOWS  /* uncomment this line to use it for windows.*/

#include "commons.h"
#include "video_cv.h"

#define channelNumbers 3

using namespace cv;
using namespace std;

int main()
{
  commons cm;
  video_cv vcv;

  string videoPath = cm.GetImageDataPath("/videos/chaplin.mp4");

  vcv.displayVideoFromPath(videoPath);

  // DESTROY ALL WINDOWS
  cout << "\n";
  destroyAllWindows();
  return 0;
}