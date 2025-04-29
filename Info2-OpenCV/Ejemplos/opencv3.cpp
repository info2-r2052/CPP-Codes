#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;

//g++ opencv3.cpp -o opencv3.e `pkg-config --cflags --libs opencv4`
//g++ opencv1.cpp -o opencv1.e -I/usr/local/include/opencv4 -L/usr/local/lib -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_videoio

 
int main() 
{
    VideoCapture stream1(0);   //0 is the id of video device.0 if you have only one camera.
    
    if (!stream1.isOpened()) 
    { //check if video device has been initialised
        cout << "cannot open camera";
    }
    
    //unconditional loop
    while (true) 
    {
        Mat cameraFrame, src_gray;
        stream1.read(cameraFrame);
        
        /// Convert it to gray
        cvtColor( cameraFrame, src_gray, COLOR_BGR2RGB );

        /// Reduce the noise so we avoid false circle detection
        GaussianBlur( src_gray, src_gray, Size(9, 9), 2, 2 );
                
        Mat imagen_procesada, rgbcanny;
        //medianBlur( cameraFrame, imagen_procesada, 10 );
        inRange(src_gray, Scalar(0,0,0), Scalar(255,0,0), imagen_procesada);
        
        Canny( src_gray, imagen_procesada, 20, 80 );
        
        
        
        /// Apply the Hough Transform to find the circles
        vector<Vec3f> circles;
        HoughCircles( imagen_procesada, circles, HOUGH_GRADIENT, 1, imagen_procesada.rows/8, 1.2, 70);

        //cvCvtColor(imagen_procesada, rgbcanny, CV_GRAY2BGR);

        for (size_t i = 0; i < circles.size(); i++)
        {
            Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
            int radius = cvRound(circles[i][2]);
            // circle center
            circle( cameraFrame, center, 3, Scalar(0,255,0), -1, 8, 0 );
            // circle outline
            circle( cameraFrame, center, radius, Scalar(0,0,255), 3, 8, 0 );
  
            //printf("x: %d y: %d r: %d\n",center.x,center.y, radius);
        }


    //cvNamedWindow("circles", 1);
    //cvShowImage("circles", rgbcanny);

        imshow("canny", imagen_procesada);
        imshow("cam", cameraFrame);
        if (waitKey(30) >= 0)
        break;
    }
    return 0;
}