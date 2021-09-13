#ifndef ZEDBOARDCLIENT_H
#define ZEDBOARDCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QTimer>
#include <QString>
#include <QtDebug>
#include <QApplication>
#include <QFile>
#include <QDataStream>
#include <QImageWriter>
#include <QBuffer>
#include <QImage>
#include <QImageReader>
#include <QQueue>
#include <QtEndian>
#include <QPixmap>
#include <QDir>
#include <QVector2D>



class zedboardClient: public QObject
{
    Q_OBJECT
public:
    explicit zedboardClient(QString ipAddress, quint16 portNumber);
    virtual ~zedboardClient();
//    QFile imgfile;
    QDir dir;
    QFile file;
    QString filename = "myImage.png";
    QString path = "C:/Users/c.eguzo/Desktop/C-EGUZO-PHD-FZ/GENERAL/Udacity_project/zedboardReceiver/";
    QImage image;


signals:
    void receiveData(QByteArray receivedData);
    void imageReady(QImage image);
    void statMessage(QString statMsg);
//    qint64 OnData(qint64 dataStream);
public slots:
    void writeData();
    void connectBoard();
    void OnconnectedBoard();
    void disconnectBoard();
    QString disconnectionStatus();
    void errorOccurred(QAbstractSocket::SocketError socketError);
    void readChannelFinished();
    qint64 readytoRead();
    qint64 processReceivedData(qint64 receivedBytes);

private:
    void reconnectBoard();
    void update();
    void writeFile(QString file, qint64 inData);
    QTcpSocket socket;
    quint16 portNumber;
    qint64 dataSize;
    QString ipAddress;
    QTimer *timer;
    QTimer networkTimer;
    char* inData;
    qint32* inputBuffer;
    qint32 outputBuffer;
    quint32 totalBytes = 4*480*640;
    quint32 receivedStream;
    quint32 receivedBytes;
    QByteArray upperlimit;// = 1229900;
    QByteArray receivedData;
    char *data;
    qint32 imgWidth = 640;
    qint32 imgHeight = 480;
    QQueue<quint32> queue;
    QQueue<quint32> bufqueue;
    quint32 accumulator;
    QByteArray incomingBytes;

};

#endif // ZEDBOARDCLIENT_H
