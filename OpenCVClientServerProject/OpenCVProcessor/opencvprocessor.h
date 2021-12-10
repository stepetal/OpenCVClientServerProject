#ifndef OPENCVPROCESSOR_H
#define OPENCVPROCESSOR_H

#include "opencvprocessor_global.h"
#include <QString>
#include <QDebug>
#include <QDataStream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

class OPENCVPROCESSORSHARED_EXPORT OpenCVProcessor
{
    cv::Mat image;//исходное изображение
    QByteArray imageWithSizeByteArray;//изображение, преобразованное в QByteArray
    cv::Mat recoveredImage;//восстановленное изображение из QByteArray
public:
    OpenCVProcessor();
    void setImage(QString pathToImage){ image = cv::imread(cv::String(pathToImage.toStdString()),cv::IMREAD_GRAYSCALE); }//исходное изображение одноканальное, 256 градаций серого
    void showOriginalImage();
    void showRecoveredImage();
    void saveReceivedImage();
    QByteArray getImageByteArray(){return imageWithSizeByteArray;}
    void setImageByteArray(QByteArray imgByteArray){imageWithSizeByteArray = imgByteArray;}
    void convertMatToByteArray();
    void convertByteArrayToMat();
};

#endif // OPENCVPROCESSOR_H
