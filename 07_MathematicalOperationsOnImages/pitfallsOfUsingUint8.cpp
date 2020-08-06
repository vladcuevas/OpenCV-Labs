// Include libraries
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <iostream> // std::cout
#include <string>   // std::string, std::to_string
#include <stdio.h> /* defines FILENAME_MAX */
// #define WINDOWS  /* uncomment this line to use it for windows.*/

#include "commons.h"
#include "image_cv.h"

#define channelNumbers 3

using namespace cv;
using namespace std;

int main()
{
  commons cm;
  image_cv icv;

  uint8_t data[] = {100,110,120,130};
  Mat a(2,2,CV_8UC1,data);

  cout << a;
  cout << "\n";
  cout << a + 130;

  // You can see that the element a[1,1] should have been 260. 
  // but instead it clipped. 
  // There will be a similar problem if we subtract.

  cout << "\n";

  uint8_t scalar = 130;
  cout << a - scalar;

  // In this case, both operands (a and 130) are uint8 and thus 
  // the output is uint8 and hence the clipping.

  // This shows a major Pitfall of using uint8 while 
  // dealing with arithmetic operations on images.

  // Thus, it is important to convert the images to int or 
  // float(recommended) data types while doing arithmetic operations 
  // (like addition, subraction multiplication etc) on images to avoid undesirable results.

  
  // Solution 1 : Use opencv functions

  Mat addition;
  add(a,Scalar(130),addition);
  cout << "\n";
  cout << addition;


  // Solution 2a: Convert to int

  // You should convert to higher integer types to avoid overflow and underflow situations. Perform clipping if necessary and bring it back to uint8 in the final stage as that is what the display functions expect.

  int dataInt[] = {100,110,120,130};
  Mat b(2,2,CV_32SC1,dataInt);
  b = b + 130;

  cout << "\n";
  cout << b;

  b.convertTo(b,CV_8UC1);
  cout << "\n";
  cout << b;

  // You can do the same with float datatype as well

  //Solution 2b: Convert to normalized float32/float64

  // It is a good practice to convert the uint8 to float 
  // and normalize the range to [0,1] and change it back 
  // to [0,255] after doing all arithmetic operations

  Mat a_float32;
  a.convertTo(a_float32,CV_32F,1.0/255.0,0);
  a_float32 = a_float32 + 130.0/255.0;
  cout << "\n";
  cout << a_float32;

  Mat c;
  a_float32.convertTo(c,CV_32F,255.0,0.0);
  cout << "\n";
  cout << c;

  // Clipped output
  Mat b_uint8;
  c.convertTo(b_uint8,CV_8UC1);
  cout << "\n";

  cout << b_uint8;

  return 0;
}