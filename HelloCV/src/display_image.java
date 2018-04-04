import org.opencv.core.Core;
import org.opencv.core.Mat;
import org.opencv.core.MatOfRect;
import org.opencv.core.Point;
import org.opencv.core.Rect;
import org.opencv.core.Scalar;
import org.opencv.highgui.Highgui;
import org.opencv.objdetect.CascadeClassifier;

import JavaOpenCV.Imshow;

public class display_image {
	 
    public static void main(String[] args) {
    	
    	System.loadLibrary(Core.NATIVE_LIBRARY_NAME);
    	Mat image = Highgui.imread("_MG_1829a.JPG");
        
        if(image.empty() == true )                              // Check for invalid input
        {
            System.out.println("Could not open or find the image");
        }
        else
        {
        	Imshow im = new Imshow("Title");
        	System.loadLibrary(Highgui.CV_
            namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
            imshow( "Display window", image );                   // Show our image inside it.
        }
    }
}