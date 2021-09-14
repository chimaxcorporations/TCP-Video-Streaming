# TCP-Video-Streaming
This is the captone project for Udacity C++ Nanodegree Program: TCP Video Streaming application
 
The TCP Video streaming application creates a client manager which connects to a remote Zedboard FPGA integrated with an 0V7670 camera. The client application displays the received image packet through a Graphic User Interface (GUI). The remote Zedboard FPGA is locally connected to the streaming client through IP: 192.168.0.9 and Port: 7.
The main goal of the application is to continuously listen to the specified port for data streaming, structure data into a 2D array for imaging, and display the image on a GUI. The project was developed with QT creator 5.
Dependencies for Running Locally
QT      += core
QT      += gui
QT      += network
QT      += multimedia
QT      += multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    zedboardclient.cpp

HEADERS += \
    mainwindow.h \
    zedboardclient.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=
Basic Build Instructions
1.	Install QT creator 4 and above.
2.	Clone the repo to your local drive
3.	Build and Run it
4.	Enter the IP address and Port number
5.	Click connect to start streaming
6.	Click disconnect to end streaming
