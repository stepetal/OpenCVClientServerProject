#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QObject>
#include <QUdpSocket>
#include <QNetworkDatagram>
#include <QHostAddress>

#include "opencvprocessor.h"

enum imageTextEnum {TEXT, IMAGE};

class DataManager : public QObject
{
    Q_OBJECT
    QUdpSocket *udpSocket;
    QNetworkDatagram *receivedDatagram;
    OpenCVProcessor *openCVProcessor;
public:
    explicit DataManager(QObject *parent = nullptr);
    void initSocket();
    void sendText(QString text);
protected:
    void sendDatagram(QByteArray payload);
    void parseDatagram(const QNetworkDatagram &datagram);
    void initOpenCVProcessor();
signals:
    void showStatusInfo(QString);
    void showReceivedText(QByteArray);
    void showReceivedImage();
public slots:
    void readPendingDatagrams();
};

#endif // DATAMANAGER_H
