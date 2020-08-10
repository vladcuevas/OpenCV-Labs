// Include libraries
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <vector>
#include <iostream> // std::cout
#include <string>   // std::string, std::to_string
#include <stdio.h> /* defines FILENAME_MAX */
#include <direct.h>
// #define WINDOWS  /* uncomment this line to use it for windows.*/

#define GetCurrentDir _getcwd
#define channelNumbers 3

using namespace cv;
using namespace std;

Point point1, point2;
Range range1, range2;
// Source image
Mat source;

std::string GetCurrentWorkingDir(void)
{
    char buff[FILENAME_MAX];
    _getcwd(buff, FILENAME_MAX);
    std::string current_working_dir(buff);
    return current_working_dir;
}

string DATA_PATH = GetCurrentWorkingDir();

// function which will be called on mouse input
void drawBouncingBox(int action, int x, int y, int flags, void *userdata)
{
    // Action to be taken when left mouse button is pressed
    if (action == EVENT_LBUTTONDOWN)
    {
        point1 = Point(x, y);
    }
    // Action to be taken when left mouse button is released
    else if (action == EVENT_LBUTTONUP)
    {
        point2 = Point(x, y);

        if (point2.y > point1.y)
          range1 = Range(point1.y, point2.y);
        else
          range1 = Range(point2.y, point1.y);

        if (point2.x > point1.x)
          range2 = Range(point1.x, point2.x);
        else
          range2 = Range(point2.x, point1.x);

        Mat croppedImage = source(range1, range2);
        imwrite(DATA_PATH+"/images/sample_cropped.jpg", croppedImage);

        rectangle(source, point1, point2, Scalar(255, 255, 0), 2, LINE_AA);

        imshow("Window", source);
    }

    if (action == EVENT_MOUSEMOVE) {
        cout << "{[(" << x << "," << y << ")]}" << endl;
    }
}

int main()
{
    string imgPath = DATA_PATH+"/images/sample.jpg";

    source = imread(imgPath, 1);

    // Make a dummy image, will be useful to clear the drawing
    Mat dummy = source.clone();
    namedWindow("Window");
    // highgui function called when mouse events occur
    setMouseCallback("Window", drawBouncingBox);
    int k=0;
    // loop until escape character is pressed
    while (k!=27)
    {
        imshow("Window", source);

        putText(
            source,
            "Choose center, and drag, Press ESC to exit and c to clear",
            Point(10, 30),
            FONT_HERSHEY_SIMPLEX, 0.7,
            Scalar(255, 255, 255), 2
        );

        k= waitKey(20) & 0xFF;
        if (k== 99)
            // Another way of cloning
            dummy.copyTo(source);
    }
    return 0;
}