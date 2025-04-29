#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QImage>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    cv::VideoCapture Stream_Temp(0);
    Stream = Stream_Temp;   //0 is the id of video device.0 if you have only one camera.

     if (!Stream.isOpened())
     { //check if video device has been initialised
         //std::cout << "cannot open camera";
     }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    cv::Mat Imagen = cv::imread("/home/gustavo/Descargas/glaciar.jpg");

    if(!Imagen.empty())
    {
        QPixmap QTImagen = QPixmap::fromImage(QImage(Imagen.data,
                                                     400,   //Imagen.cols
                                                     400,   //Imagen.rows
                                                     Imagen.step,
                                                     QImage::Format_RGB888));

        ui->label->setPixmap(QTImagen);
        //cv::imshow("Imagen", Imagen);
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    cv::Mat cameraFrame;

    Stream.read(cameraFrame);

    if(!cameraFrame.empty())
    {
        QPixmap QTImagen = QPixmap::fromImage(QImage(cameraFrame.data,
                                                     cameraFrame.cols,
                                                     cameraFrame.rows,
                                                     cameraFrame.step,
                                                     QImage::Format_RGB888));

        ui->label_2->setPixmap(QTImagen);
    }
}
