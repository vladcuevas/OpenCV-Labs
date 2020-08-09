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

  int width = cap2.get(CAP_PROP_FRAME_WIDTH);
  int height = cap2.get(CAP_PROP_FRAME_HEIGHT);

  cout << width << "," << height << endl;

  // Read the first frame
  Mat frame;
  cap2 >> frame;
  
  icv.displayImage(frame);

  // Setting the video properties

  // Set position of video to 2.5 seconds
  cap2.set(CAP_PROP_POS_MSEC, 2500);

  // Width
  cap2.set(CAP_PROP_FRAME_WIDTH, 320);

  // Height
  cap2.set(CAP_PROP_FRAME_HEIGHT, 180);

  cap2 >> frame;

  icv.displayImage(frame);

  cout << frame.size() << endl;

  // DESTROY ALL WINDOWS
  cout << "\n";
  destroyAllWindows();
  return 0;
}