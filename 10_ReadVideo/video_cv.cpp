// Include libraries
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <iostream> // std::cout
#include <string>   // std::string, std::to_string

#include <stdio.h> /* defines FILENAME_MAX */
// #define WINDOWS  /* uncomment this line to use it for windows.*/

#include <direct.h>

#include "video_cv.h"
#define GetCurrentDir _getcwd

using namespace cv;
using namespace std;

VideoCapture video_cv::displayVideoFromPath(string videoPath, bool isDisplay, int delay)
{
  VideoCapture cap(videoPath);

  // Check if camera opened successfully
  if(!cap.isOpened()){
      cout << "Error opening video stream or file" << endl;
  }

  if (isDisplay == true) {

    // Read until video is completed
    while(cap.isOpened()){

        Mat frame;

        // Capture frame-by-frame
        cap >> frame;

        // If the frame is empty, break immediately
        if (frame.empty())
          break;

        // Write the frame into the file 'outputChaplin.mp4'
        imshow("Frame", frame);

        // Wait for 25 ms before moving on to the next frame
        // This will slow down the video 
        waitKey(25);
    }

    destroyAllWindows();

  }

  VideoCapture cap2(videoPath);

  return cap2;
}