#include "datamanager.h"

DataManager::DataManager(QObject *parent) : QObject(parent)
{
    initSocket();
    initOpenCVProcessor();
}

void DataManager::sendData(QByteArray payload)
{
    QDataStream payloadDataStream(&payload,QIODevice::ReadOnly);
    while(!payloadDataStream.atEnd())
    {
        int dataType;
        QString data;
        payloadDataStream >> dataType >> data;
        switch (static_cast<imageTextEnum>(dataType))
        {
            case imageTextEnum::TEXT:
            {
                QByteArray textTypeWithDataByteArray;
                QDataStream textDataStream(&textTypeWithDataByteArray,QIODevice::WriteOnly);
                textDataStream << dataType << data.toUtf8();
                sendDatagram(textTypeWithDataByteArray);
                break;
            }
            case imageTextEnum::IMAGE:
            {
                openCVProcessor->setImage(data);
                openCVProcessor->showOriginalImage();
                openCVProcessor->convertMatToByteArray();
                QByteArray imageTypeWithDataByteArray;
                QDataStream imageDataStream(&imageTypeWithDataByteArray,QIODevice::WriteOnly);
                imageDataStream << dataType << openCVProcessor->getImageByteArray();
                sendDatagram(imageTypeWithDataByteArray);
            }
            default:
                break;
        }
    }
}

void DataManager::initSocket()
{
    udpSocket = new QUdpSocket(this);
    QHostAddress hostAddress("127.0.0.1");
    int portNumb = 15682;
    udpSocket->bind(hostAddress,portNumb);
    connect(udpSocket,SIGNAL(readyRead()),this,SLOT(readPendingDatagrams()));
}

void DataManager::sendDatagram(QByteArray payload)
{
    QNetworkDatagram datagram(payload,QHostAddress("127.0.0.1"),15680);
    if(datagram.isValid()){
        qint64 bytesWritten = udpSocket->writeDatagram(datagram);
        if ( bytesWritten != -1){
            QString bytesWrittenStr = QString::number(bytesWritten);
            emit QString("Successfully written: " + bytesWrittenStr + ";" + "Server: " + datagram.destinationAddress().toString() +
                                           ":" + QString::number(datagram.destinationPort()));
        }
    }
}

void DataManager::initOpenCVProcessor()
{
    openCVProcessor = new OpenCVProcessor();
}

void DataManager::sendText(QString text)
{
    sendDatagram(text.toUtf8());
}

void DataManager::sendImage(QString imageName)
{

    //нужно получить массив байтов, соответствующих исходному
    //изображению
    openCVProcessor->setImage(imageName);
    openCVProcessor->showOriginalImage();
    openCVProcessor->convertMatToByteArray();
    sendDatagram(openCVProcessor->getImageByteArray());
    //openCVProcessor->convertByteArrayToMat();
    //QByteArray imageWithSizeByteArray = openCVProcessor->getImageByteArray();
    //openCVProcessor->convertByteArrayToMat();
    //openCVProcessor->showRecoveredImage();
}

void DataManager::parseDatagram(const QNetworkDatagram &datagram)
{
    QByteArray receivedByteArray = datagram.data();
    emit showReceivedInfo(receivedByteArray);
}

void DataManager::readPendingDatagrams()
{
    while(udpSocket->hasPendingDatagrams()){
        QNetworkDatagram datagram = udpSocket->receiveDatagram();
        parseDatagram(datagram);
    }
}
