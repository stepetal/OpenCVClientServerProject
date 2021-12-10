#include "opencvprocessor.h"



OpenCVProcessor::OpenCVProcessor()
{
}

void OpenCVProcessor::showOriginalImage()
{
    if(!image.empty()){
        cv::imshow("Original image (256 grayscale)", image);
    }
}

void OpenCVProcessor::showRecoveredImage()
{
    if(!recoveredImage.empty()){
        cv::imshow("Recovered image (256 grayscale)", recoveredImage);
    }
}

void OpenCVProcessor::saveReceivedImage()
{
    if(!recoveredImage.empty())
    {
        cv::imwrite("received_image.jpg",recoveredImage);
    }
}

void OpenCVProcessor::convertMatToByteArray()
{
    QByteArray imageByteArray;
    QDataStream imageByteArrayDataStream(&imageWithSizeByteArray, QIODevice::WriteOnly);
    for(int i = 0; i < image.rows;i++){
        for(int j = 0; j < image.cols;j++){
            imageByteArray.append(image.at<unsigned char>(i, j));
        }
    }
    imageByteArrayDataStream << imageByteArray << image.rows << image.cols;
}

void OpenCVProcessor::convertByteArrayToMat()
{
    if(!imageWithSizeByteArray.isEmpty()){
        QDataStream imageWithSizeDataStream(&imageWithSizeByteArray,QIODevice::ReadOnly);
        QByteArray imageByteArray;
        auto rows_numb{0};
        auto cols_numb{0};
        while(!imageWithSizeDataStream.atEnd()){
            imageWithSizeDataStream >> imageByteArray >> rows_numb >> cols_numb;
        }
        recoveredImage = cv::Mat(rows_numb,cols_numb,CV_8U);
        int i{0};
        int j{0};
        foreach (auto imageByte, imageByteArray) {
            if(j == (cols_numb )){//количество строк увеличиваем тогда, когда все столбцы пройдены
                                  //при этом сбрасывается счетчик столбцов
                i++;
                j = 0;
            }
            recoveredImage.at<unsigned char>(i,j) = (unsigned char)imageByte;
            j++;
        }
    }
}
