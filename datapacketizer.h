#ifndef DATAPACKETIZER_H
#define DATAPACKETIZER_H
#include "zedboardclient.h"


class dataPacketizer : public zedboardClient
{

public:
    explicit dataPacketizer();
    zedboardClient client;
    void dataExtractor();
signals:

};

#endif // DATAPACKETIZER_H
