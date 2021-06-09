#include <iostream>
#include "dataPath.hpp"

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

int main(){
string imagePath = DATA_PATH + "images/Contour.png";

Mat image = imread(imagePath);
Mat imageCopy = image.clone();

Mat imageGray;
// Convert to grayscale
cvtColor(image,imageGray,COLOR_BGR2GRAY);

imshow("image",imageGray);
waitKey(0);
// Find all contours in the image
vector<vector<Point> > contours;
vector<Vec4i> hierarchy;

findContours(imageGray, contours, hierarchy, RETR_LIST, CHAIN_APPROX_SIMPLE);

cout << "Number of contours found = " << contours.size();

drawContours(image, contours, -1, Scalar(0,255,0), 6);

imshow("image",image);
waitKey(0);

// Find external contours in the image
findContours(imageGray, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
cout << "Number of contours found = " << contours.size();

image = imageCopy.clone();

// Draw all the contours
drawContours(image, contours, -1, Scalar(0,255,0), 3);

imshow("image",image);
waitKey(0);


// Draw only the 3rd contour
// Note that right now we do not know
// the numbering of contour in terms of the shapes
// present in the figure
image = imageCopy.clone();
drawContours(image, contours, 2, Scalar(0,255,0), 3);

imshow("image",image);
waitKey(0);


// Find all contours in the image
findContours(imageGray, contours, hierarchy, RETR_LIST, CHAIN_APPROX_SIMPLE);
// Draw all the contours
drawContours(image, contours, -1, Scalar(0,255,0), 3);

Moments M;
int x,y;
for (size_t i=0; i < contours.size(); i++){
    // We will use the contour moments
    // to find the centroid
    M = moments(contours[i]);
    x = int(M.m10/double(M.m00));
    y = int(M.m01/double(M.m00));

    // Mark the center
    circle(image, Point(x,y), 10, Scalar(255,0,0), -1);
}

imshow("image",image);
waitKey(0);


for (size_t i=0; i < contours.size(); i++){
    // We will use the contour moments
    // to find the centroid
    M = moments(contours[i]);
    x = int(M.m10/double(M.m00));
    y = int(M.m01/double(M.m00));

    // Mark the center
    circle(image, Point(x,y), 10, Scalar(255,0,0), -1);

    // Mark the contour number
    putText(image, to_string(i+1), Point(x+40,y-10), FONT_HERSHEY_SIMPLEX, 1, Scalar(0,0,255),2);
}

imageCopy = image.clone();

imshow("image",image);
waitKey(0);

double area;
double perimeter;
for (size_t i=0; i < contours.size(); i++){
    area = contourArea(contours[i]);
    perimeter = arcLength(contours[i],true);
    cout << "Contour #" << i+1 << " has area = " << area << " and perimeter = " << perimeter << endl;
}

image = imageCopy.clone();
Rect rect;
for (size_t i=0; i < contours.size(); i++){
    // Vertical rectangle
    rect = boundingRect(contours[i]);
    rectangle(image, rect, Scalar(255,0,255), 2);
}
imshow("image",image);
waitKey(0);


image = imageCopy.clone();
RotatedRect rotrect;
Point2f rect_points[4];
Mat boxPoints2f,boxPointsCov;

for (size_t i=0; i < contours.size(); i++){
    // Rotated rectangle
    rotrect = minAreaRect(contours[i]);
    boxPoints(rotrect, boxPoints2f);
    boxPoints2f.assignTo(boxPointsCov,CV_32S);
    polylines(image, boxPointsCov, true, Scalar(0,255,255), 2);
}

imshow("image",image);
waitKey(0);

image = imageCopy.clone();
Point2f center;
float radius;
for (size_t i=0; i < contours.size(); i++){
    // Fit a circle
    minEnclosingCircle(contours[i],center,radius);
    circle(image,center,radius, Scalar(125,125,125), 2);
}

imshow("image",image);
waitKey(0);


image = imageCopy.clone();
RotatedRect rellipse;
for (size_t i=0; i < contours.size(); i++){
    // Fit an ellipse
    // We can fit an ellipse only
    // when our contour has minimum
    // 5 points
    if (contours[i].size() < 5)
        continue;
    rellipse = fitEllipse(contours[i]);
    ellipse(image, rellipse, Scalar(255,0,125), 2);
}
imshow("image",image);
waitKey(0);

return 0;
}
