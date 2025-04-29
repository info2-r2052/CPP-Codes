#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QImage>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    cv::VideoCapture Stream_Temp(0);
    Stream = Stream_Temp;   //0 is the id of video device.0 if you have only one camera.

     if (!Stream.isOpened())
     { //check if video device has been initialised
         //std::cout << "cannot open camera";
     }

     // Crea e inicializa el temporizador
     timer = new QTimer(this);
     connect(timer, &QTimer::timeout, this, &MainWindow::captureFrame);

     // Inicia el temporizador, se ejecutará cada 30 ms (aproximadamente 33 fps)
     timer->start(30);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::captureFrame()
{
    cv::Mat frame;
    Stream >> frame; // Captura el frame de la cámara

    if (frame.empty()) {
        return;
    }

    // Convierte de BGR a RGB
    cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);

    QGraphicsScene *scene = new QGraphicsScene(this);
    QImage img((const unsigned char*) frame.data, frame.cols, frame.rows, QImage::Format_RGB888);
    scene->addPixmap(QPixmap::fromImage(img));
    ui->graphicsView->setScene(scene);
}


void MainWindow::on_pushButton_Iniciar_clicked()
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

        ui->label_Display->setPixmap(QTImagen);
    }
}

