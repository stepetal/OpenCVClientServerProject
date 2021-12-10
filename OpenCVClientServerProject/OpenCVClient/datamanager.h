#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QObject>
#include <QUdpSocket>
#include <QNetworkDatagram>
#include <QHostAddress>

#include "opencvprocessor.h"

// данное перечисление будет использоваться также на серверной стороне
// для контроля за типом принятой информации
enum imageTextEnum {TEXT, IMAGE};

class DataManager : public QObject
{
    Q_OBJECT
    QUdpSocket *udpSocket;
    QNetworkDatagram *receivedDatagram;
    OpenCVProcessor *openCVProcessor;
public:
    explicit DataManager(QObject *parent = nullptr);
    void sendData(QByteArray payload);
    void sendText(QString text);
    void sendImage(QString imageName);
protected:
    void sendDatagram(QByteArray payload);
    void parseDatagram(const QNetworkDatagram &datagram);
    void initSocket();
    void initOpenCVProcessor();
signals:
    void showStatusInfo(QString);
    void showReceivedInfo(QByteArray);
public slots:
    void readPendingDatagrams();
};

#endif // DATAMANAGER_H
