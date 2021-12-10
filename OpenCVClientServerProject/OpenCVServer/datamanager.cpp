#include "datamanager.h"

DataManager::DataManager(QObject *parent) : QObject(parent)
{
    initSocket();
    initOpenCVProcessor();
}

void DataManager::initOpenCVProcessor()
{
    openCVProcessor = new OpenCVProcessor();
}

void DataManager::initSocket()
{
    udpSocket = new QUdpSocket(this);
    QHostAddress hostAddress("127.0.0.1");
    int portNumb = 15680;
    udpSocket->bind(hostAddress,portNumb);
    connect(udpSocket,SIGNAL(readyRead()),this,SLOT(readPendingDatagrams()));
}

void DataManager::sendText(QString text)
{
    sendDatagram(text.toUtf8());
}

void DataManager::sendDatagram(QByteArray payload)
{
    QNetworkDatagram datagram(payload,QHostAddress("127.0.0.1"),15682);
    if(datagram.isValid()){
        qint64 bytesWritten = udpSocket->writeDatagram(datagram);
        if ( bytesWritten != -1){
            QString bytesWrittenStr = QString::number(bytesWritten);
            emit QString("Successfully written: " + bytesWrittenStr + ";" + "Server: " + datagram.destinationAddress().toString() +
                                           ":" + QString::number(datagram.destinationPort()));
        }
    }
}

void DataManager::parseDatagram(const QNetworkDatagram &datagram)
{
    QByteArray receivedByteArray = datagram.data();
    QDataStream payloadDataStream(&receivedByteArray,QIODevice::ReadOnly);
    while(!payloadDataStream.atEnd())
    {
        int dataType;
        QByteArray data;
        payloadDataStream >> dataType >> data;
        switch (static_cast<imageTextEnum>(dataType))
        {
            case imageTextEnum::TEXT:
            {
                emit showReceivedText(data);
                break;
            }
            case imageTextEnum::IMAGE:
            {
                openCVProcessor->setImageByteArray(data);
                openCVProcessor->convertByteArrayToMat();
                openCVProcessor->saveReceivedImage();
                openCVProcessor->showRecoveredImage();
                break;
            }
            default:
                break;
        }
    }
}

void DataManager::readPendingDatagrams()
{
    while(udpSocket->hasPendingDatagrams()){
        QNetworkDatagram datagram = udpSocket->receiveDatagram();
        parseDatagram(datagram);
    }
}
