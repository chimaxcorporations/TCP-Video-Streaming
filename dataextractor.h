#ifndef DATAEXTRACTOR_H
#define DATAEXTRACTOR_H
#include "zedboardclient.h"

class dataExtractor:public QObject
{
    Q_OBJECT
    qint64 dataStream;
    QString Add;
    quint16 portNum;

public:
    dataExtractor();
    zedboardClient *client = new zedboardClient(Add,portNum);


public slots:
    qint64 dataUnpack();
};

#endif // DATAEXTRACTOR_H
