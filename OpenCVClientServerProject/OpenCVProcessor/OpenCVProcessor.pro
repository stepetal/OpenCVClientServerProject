#-------------------------------------------------
#
# Project created by QtCreator 2020-12-03T15:14:55
#
#-------------------------------------------------

QT       -= gui
QT += core

TARGET = OpenCVProcessor
TEMPLATE = lib

DEFINES += OPENCVPROCESSOR_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        opencvprocessor.cpp

HEADERS += \
        opencvprocessor.h \
        opencvprocessor_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -LF:/OpenCV/opencv/lib/Release/ -lopencv_calib3d450
else:win32:CONFIG(debug, debug|release): LIBS += -LF:/OpenCV/opencv/lib/Debug/ -lopencv_calib3d450d

win32:CONFIG(release, debug|release): LIBS += -LF:/OpenCV/opencv/lib/Release/ -lopencv_core450
else:win32:CONFIG(debug, debug|release): LIBS += -LF:/OpenCV/opencv/lib/Debug/ -lopencv_core450d

win32:CONFIG(release, debug|release): LIBS += -LF:/OpenCV/opencv/lib/Release/ -lopencv_highgui450
else:win32:CONFIG(debug, debug|release): LIBS += -LF:/OpenCV/opencv/lib/Debug/ -lopencv_highgui450d

win32:CONFIG(release, debug|release): LIBS += -LF:/OpenCV/opencv/lib/Release/ -lopencv_imgproc450
else:win32:CONFIG(debug, debug|release): LIBS += -LF:/OpenCV/opencv/lib/Debug/ -lopencv_imgproc450d

win32:CONFIG(release, debug|release): LIBS += -LF:/OpenCV/opencv/lib/Release/ -lopencv_features2d450
else:win32:CONFIG(debug, debug|release): LIBS += -LF:/OpenCV/opencv/lib/Debug/ -lopencv_features2d450d

win32:CONFIG(release, debug|release): LIBS += -LF:/OpenCV/opencv/lib/Release/ -lopencv_imgcodecs450
else:win32:CONFIG(debug, debug|release): LIBS += -LF:/OpenCV/opencv/lib/Debug/ -lopencv_imgcodecs450d



INCLUDEPATH += F:/OpenCV/opencv/include
DEPENDPATH += F:/OpenCV/opencv/include
