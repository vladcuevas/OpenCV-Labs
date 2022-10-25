// Include libraries
#include <iostream>
// #include "includeLibraries.h"
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <time.h>
#include "dataPath.hpp"
#include <filesystem>
#include <string>
#include <format>

using namespace std;
using namespace cv;

namespace fs = std::filesystem;

// Piecewise Linear interpolation implemented on a particular Channel   
void interp(float* fullRange,float* Curve, float* originalValue, uchar* lut)
{
  int i;
  for (i = 0; i < 256; i++)
  {
    int j = 0;
    float a = fullRange[i];
    while(a > originalValue[j])
    {
      j++;
    }
    if (a == originalValue[j])
    {
      lut[i] = Curve[j];
      continue;
    }
    float slope = ((float)(Curve[j] - Curve[j-1])) /
                        (originalValue[j] - originalValue[j-1]);
    float constant = Curve[j] - slope * originalValue[j];
    lut[i] = slope * fullRange[i] + constant;
  }
}

int main(int argc, char *argv[])
{
    // This program can be executed as an example without parameters
    // also, can be called with two parameters,
    // the first parameter is the image path
    // the second parameter is 0 (to run without showing the images, aka silent mode)
    // or 1 (to run showing the images)
    // by default it will show the images, because this is an example

    std::string img_path = fs::current_path().parent_path().generic_string() + DATA_PATH + "images/girl.jpg";

    int isImShow = 1;
    int filterCode = 0;
    fs::path fs_path = fs::path{img_path};
    fs::path parentStem;

    if (argc > 1) {
        img_path = argv[1];
        fs_path = fs::path{img_path};
        parentStem = fs_path.parent_path()/fs_path.stem();

        try
        {
            isImShow = stoul(argv[2],nullptr,0);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            isImShow = 0;
        }
    }

    if (fs::exists(fs_path)) {
        // Read image
        // First, we read the image from a file specified by the filename. We create a copy of the original image to serve as a placeholder for output.
        Mat img = imread(img_path);

        // Start lookup
        // Next, we specify the intensity values in the R and B channels on the original curve ( black dashed line ) 
        // that needs to be modified as explained earlier. 
        // We create a lookUp table to store the interpolated values of the curves.

        // Pivot points for X-Coordinates
        float originalValue[] = {0,50,100,150,200,255};

        // Changed points on Y-axis for each channel
        float rCurve[] = {0,80,150,190,220,255};
        float bCurve[] = {0,20,40,75,150,255};

        // Splitting the channels
        vector<Mat> channels(3);
        split(img, channels); 

        // Create a LookUp Table
        float fullRange[256];
        int i;
        for(i=0;i<256;i++)
        {
        fullRange[i]= (float)i;
        }               
        Mat lookUpTable(1, 256, CV_8U); 
        uchar* lut = lookUpTable.ptr();
        // End lookup

        // Start Interpolate
        // Interpolate the values specified by the pivot points and store it in the lookUp table 
        // to get a mapping from the original values to the modified values for each intensity level. 
        // Then we use the lookUp Table to map the pixel values in the original image to the output 
        // image for both the channels and merge the modified channels to get the final output.

        Mat bLUT, rLUT;
        // Apply interpolation and create look up table
        interp(fullRange,bCurve,originalValue,lut);

        // Apply mapping and check for underflow/overflow in Blue Channel
        LUT(channels[0],lookUpTable,bLUT);
        min(bLUT,255,bLUT);
        max(bLUT,0,bLUT); 

        // Apply interpolation and create look up table
        interp(fullRange,rCurve,originalValue,lut);

        // Apply mapping and check for underflow/overflow in Red Channel
        LUT(channels[2],lookUpTable,rLUT);
        min(rLUT,255,rLUT);
        max(rLUT,0,rLUT);
        // End Interpolate

        // Start Concatenate
        Mat output;
        // Merge the channels 
        vector<Mat> modifiedChannels = {bLUT, channels[1], rLUT};
        merge(modifiedChannels,output); 

        // Display the images
        Mat combined;
        cv::hconcat(img, output, combined);
        // End Concatenate

        Mat imhsv;
        cvtColor(img, imhsv, COLOR_BGR2HSV);

        Mat imhsvClahe = imhsv.clone();

        vector<Mat> imhsvChannels(3);
        split(imhsv,imhsvChannels);

        // Equalize histogram
        // Perform histogram equalization only on the V channel
        equalizeHist(imhsvChannels[2],imhsvChannels[2]);

        // Start CLAHE
        Ptr<CLAHE> clahe = createCLAHE(2.0, Size(8,8));
        vector<Mat> imhsvClaheChannels(3);
        split(imhsvClahe,imhsvClaheChannels);
        clahe->apply(imhsvClaheChannels[2],imhsvClaheChannels[2]);
        merge(imhsvClaheChannels,imhsvClahe);

        Mat imEqCLAHE;
        cvtColor(imhsvClahe, imEqCLAHE, COLOR_HSV2BGR);
        // End CLAHE

        merge(imhsvChannels,imhsv);
        // Convert back to BGR format
        Mat imEq;
        cvtColor(imhsv,imEq, COLOR_HSV2BGR);
        
        if (isImShow == 1) {
            imshow("Original Image", img);
            waitKey(0);

            imshow("Warming filter output", combined);
            waitKey(0);
        }

        if (argc > 1) {
            std::string newPath = std::format(
                "{}_eq_curves{}", 
                parentStem.generic_string(),
                fs_path.extension().generic_string()
            );

            cout << newPath << endl;
            imwrite(newPath, imEqCLAHE);
        }
    }
    else {
        cout << "The provided path " << img_path << " is not valid!";
    }

    return 0;
}
