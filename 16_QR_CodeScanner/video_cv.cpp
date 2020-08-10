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
    if (!cap.isOpened()) {
        cout << "Error opening video stream or file" << endl;
    }

    if (isDisplay == true)
        read_video(cap);

    VideoCapture cap2(videoPath);

    return cap2;
}

void video_cv::write_video(VideoCapture cap, int fps, string writePath)
{
    // Write the frame into the file 'outputChaplin.mp4'
    int frame_width = cap.get(CAP_PROP_FRAME_WIDTH);
    int frame_height = cap.get(CAP_PROP_FRAME_HEIGHT);

    // Define the codec and create VideoWriter object.
    // The output is stored in 'outputChaplin.mp4' file.
    VideoWriter out(
        writePath,
        VideoWriter::fourcc('M', 'J', 'P', 'G'),
        fps,
        Size(
            frame_width,
            frame_height
        )
    );

    read_video(cap, out);

    // When everything done, release the VideoCapture and VideoWriter objects
    cap.release();
    out.release();
}

void video_cv::read_video(VideoCapture cap, VideoWriter out)
{
    // Read until video is completed
    while (cap.isOpened()) {

        Mat frame;

        // Capture frame-by-frame
        cap >> frame;

        // If the frame is empty, break immediately
        if (frame.empty())
            break;

        // Write the frame into the file 'outputChaplin.mp4'
        if (out.isOpened()==true)
          out.write(frame);
        imshow("Frame", frame);

        // Wait for 25 ms before moving on to the next frame
        // This will slow down the video 
        waitKey(25);
    }

    destroyAllWindows();
}