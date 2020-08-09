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
#include "image_cv.h"

#define channelNumbers 3

using namespace cv;
using namespace std;

int main()
{
  commons cm;
  video_cv vcv;
  image_cv icv;

  string videoPath = cm.GetImageDataPath("/videos/chaplin.mp4");

  VideoCapture cap2 = vcv.displayVideoFromPath(videoPath, false);

  int frame_width = cap2.get(CAP_PROP_FRAME_WIDTH);
  int frame_height = cap2.get(CAP_PROP_FRAME_HEIGHT);

  cout << frame_width << "," << frame_height << endl;

  vcv.write_video(
    cap2,
    60,
    cm.GetImageDataPath("/videos/outputChaplin.mp4")
  );

  return 0;
}