#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    cv::VideoCapture    Stream;
    QTimer              *timer; // El temporizador

private slots:
    void captureFrame();
    void on_pushButton_Iniciar_clicked();

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
