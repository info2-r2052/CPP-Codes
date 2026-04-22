#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;
 
int main() 
{
    //create a gui window:
    //namedWindow("Output",1);
    
    //ileo la imagen
    Mat imagen = imread("homero.jpg", 0);
    Mat output;

                    //write text on the matrix:
    /*putText(output,
                                    "Hello World :)",
                                    cv::Point(15,70),
                                    FONT_HERSHEY_PLAIN,
                                    1,
                                    cv::Scalar(0,255,0),
                                    4);*/
    
    //display the image:
    //imshow("Output", output);
    std::cout << "Imagen Leida!" << "\r\n";

    Canny(imagen, output, 100, 200);

    std::cout << "Imagen Procesada!" << std::endl;

    imwrite("./imagen/salida.jpeg", output);
    
    std::cout << "Imagen modificada guardada!" << std::endl;

     return 0;
}