#-------------------------------------------------
#
# Project created by QtCreator 2018-05-29T16:14:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QTOpenCV
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp


HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

CONFIG += link_pkgconfig
PKGCONFIG += opencv

INCLUDEPATH += /usr/local/include

LIBS += -L/user/local/lib -lopencv_core -lopencv_imgproc -lopencv_imgcodecs -lopencv_highgui -lz
