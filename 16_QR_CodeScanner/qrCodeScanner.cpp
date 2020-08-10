// Include libraries
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <vector>
#include <iostream> // std::cout
#include <string>   // std::string, std::to_string
#include <stdio.h> /* defines FILENAME_MAX */
// #define WINDOWS  /* uncomment this line to use it for windows.*/

#include "commons.h"
#include "image_cv.h"

#define channelNumbers 3

using namespace cv;
using namespace std;

// void display(Mat &im, Mat &bbox)
// {
//     int n = bbox.rows;
//     for (int i = 0; i < n; i++)
//     {
//         line(
//           im, 
//           Point2i(bbox.at<float>(i, 0), bbox.at<float>(i, 1)), 
//           Point2i(bbox.at<float>((i+1) % n, 0), 
//           bbox.at<float>((i+1) % n, 1)), 
//           Scalar(255, 0, 0), 3
//         );
//     }
//     imshow("Result", im);
// }

int main(int argc, char* argv[])
{
    image_cv icv;
    commons cm;
    string imgPath = cm.GetImageDataPath("/images/qr_loren.png");
    
    Mat inputImage;

    if(argc>1)
	    inputImage = imread(argv[1]);
	  else
	    inputImage = imread(imgPath);

    icv.displayImage(inputImage);

    QRCodeDetector qrDecoder;

    Mat bbox, rectifiedImage;

    std::string data = qrDecoder.detectAndDecode(inputImage, bbox, rectifiedImage);
    if (data.length()>0)
    {
        cout << "Decoded Data : " << data << endl;

        //display(inputImage, bbox);
        // rectifiedImage.convertTo(rectifiedImage, CV_8UC3);
        // imshow("Rectified QRCode", rectifiedImage);

        // waitKey(0);
    }
    else
        cout << "QR Code not detected" << endl;

    // DESTROY ALL WINDOWS
    cout << "\n";
    destroyAllWindows();
    return 0;
}