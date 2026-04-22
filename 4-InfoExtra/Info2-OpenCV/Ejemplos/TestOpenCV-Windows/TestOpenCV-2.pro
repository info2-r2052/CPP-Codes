QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -LG:/Sistemas/opencv_4_9_0/opencv/build/x64/vc16/lib/ -lopencv_world490
else:win32:CONFIG(debug, debug|release): LIBS += -LG:/Sistemas/opencv_4_9_0/opencv/build/x64/vc16/lib/ -lopencv_world490d
else:unix: LIBS += -LG:/Sistemas/opencv_4_9_0/opencv/build/x64/vc16/lib/ -lopencv_world490

INCLUDEPATH += G:/Sistemas/opencv_4_9_0/opencv/build/x64/vc16
INCLUDEPATH += G:/Sistemas/opencv_4_9_0/opencv/build/include
DEPENDPATH += G:/Sistemas/opencv_4_9_0/opencv/build/x64/vc16
