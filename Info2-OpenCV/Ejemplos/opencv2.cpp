#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;

//g++ opencv2.cpp -o opencv2.e `pkg-config --cflags --libs opencv4`
 
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
        Mat cameraFrame;
        stream1.read(cameraFrame);
        
        Mat imagen_procesada;
        Canny( cameraFrame, imagen_procesada, 100, 200 );
        
        imshow("cam", imagen_procesada);
        if (waitKey(30) >= 0)
        break;
    }
    return 0;
}