// Include libraries
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <vector>
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

// Points to store the center of the circle and a point on the circumference
Point center, circumference;
// Source image
Mat source;

// function which will be called on mouse input
void drawCircle(int action, int x, int y, int flags, void *userdata)
{
    // Action to be taken when left mouse button is pressed
    if (action == EVENT_LBUTTONDOWN)
    {
        center = Point(x, y);
        // Mark the center
        circle(source, center, 1, Scalar(255, 255, 0), 2, LINE_AA);
    }
    // Action to be taken when left mouse button is released
    else if (action == EVENT_LBUTTONUP)
    {
        circumference = Point(x, y);
        // Calculate radius of the circle
        float radius = sqrt(pow(center.x-circumference.x, 2)+pow(center.y-circumference.y, 2));
        // Draw the circle
        circle(source, center, radius, Scalar(0, 255, 0), 2, LINE_AA);
        imshow("Window", source);
    }
}

int main()
{
    commons cm;
    string imgPath = cm.GetImageDataPath("/images/sample.jpg");
    source = imread(imgPath, 1);

    // Make a dummy image, will be useful to clear the drawing
    Mat dummy = source.clone();
    namedWindow("Window");
    // highgui function called when mouse events occur
    setMouseCallback("Window", drawCircle);
    int k=0;
    // loop until escape character is pressed
    while (k!=27)
    {
        imshow("Window", source);
        putText(source, "Choose center, and drag, Press ESC to exit and c to clear", Point(10, 30), FONT_HERSHEY_SIMPLEX, 0.7, Scalar(255, 255, 255), 2);
        k= waitKey(20) & 0xFF;
        if (k== 99)
            // Another way of cloning
            dummy.copyTo(source);
    }
    return 0;
}