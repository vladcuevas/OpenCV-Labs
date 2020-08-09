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

class video_cv {
public:

  void read_video(VideoCapture cap, VideoWriter out=VideoWriter());
  void write_video(VideoCapture cap, int fps, string writePath);
  VideoCapture displayVideoFromPath(string videoPath, bool isDisplay=true, int delay=25);

};