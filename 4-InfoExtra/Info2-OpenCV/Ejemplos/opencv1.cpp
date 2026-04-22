#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;

//g++ opencv1.cpp -o opencv1.e -I/usr/local/include/opencv4 -L/usr/local/lib -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_videoio

//g++ opencv1.cpp -o opencv1.e `pkg-config --modversion opencv4`
 
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
        imshow("cam", cameraFrame);
        if (waitKey(500) >= 0)
        break;
    }
    return 0;
}
