/* This Program implements a TCP socket for streaming camera data from a remote FPGA connected
 * to IP: 192.168.0.9 port 7.
 * 1. A signal-slot connection is established
 * 2. Connection is established
 * 3. A write  string is sent to request data
 * 4. Data sent and read when ready
 * 5. Process is continued until socket is closed
 * In the event of an error, An error message is issued.
 */

#include "zedboardclient.h"
#include <QUrl>
zedboardClient::zedboardClient(QString ipAddress, quint16 portNumber):QObject(nullptr),socket(this),
    portNumber(portNumber),
    ipAddress(ipAddress),
    timer(NULL)
{
    //connect signals to slot
    connect(&socket, &QTcpSocket::connected,this, &zedboardClient::OnconnectedBoard);// Establish connection to board
    connect(&socket, &QAbstractSocket::errorOccurred, this, &zedboardClient::errorOccurred);// what happens when there is error
    connect(&socket, &QTcpSocket::disconnected, this, &zedboardClient::disconnectionStatus);// Disconnect from board
    connect(&socket, &QTcpSocket::readyRead, this,  &zedboardClient::readytoRead);// Read data from board
    connect(&socket, &QTcpSocket::readChannelFinished, this,  &zedboardClient::readChannelFinished);// Read data from board

    // Setup connection
    //    connectBoard();

}
// Zedboard class destructor
zedboardClient::~zedboardClient()
{
    socket.close();
    if (timer != NULL)
    {
        delete timer;
    }
}
// Write request string sent
void zedboardClient::writeData()
{
    QByteArray cmdData;
    cmdData.append("1");// request string
    // TODO: Check again whether you can actually send data
    socket.write(cmdData);
}
// Time based system loop
void zedboardClient::update()
{
//    qDebug("FPGAClient : On Update");
//     emit statMessage("FPGAClient : On Update");
    writeData();
}


//Establish connection with remote device (server)
void zedboardClient::connectBoard()
{
    qDebug("FPGAClient : Connecting ...");
    socket.connectToHost(ipAddress,portNumber);
    if(socket.waitForConnected(3000))
    {
        qDebug("FPGAClient : Connected to FPGA card !");
         emit statMessage("FPGAClient : Connected to FPGA card !");
        timer = new QTimer(this);
        if (timer != NULL)
        {
            connect(timer, &QTimer::timeout, this, QOverload<>::of(&zedboardClient::update));
            timer->start(100);
        }
    } else {

        qDebug("FPGAClient : Connecting to FPGA card Failed!");
        emit statMessage("FPGAClient : Connecting to FPGA card Failed!");
    }
}


void zedboardClient::OnconnectedBoard()
{
    qDebug("FPGAClient : Connected !");
}

// Disconnect board
void zedboardClient::disconnectBoard()
{
    qDebug()<< "On disconnect Board";
    socket.close();
     emit statMessage("On disconnect Board");
    if (timer != NULL)
    {
        delete timer;
    }

}
// On disconnection status
QString zedboardClient::disconnectionStatus()
{
    qDebug()<<"On Disconnection status";
    reconnectBoard();
    return "Reconnecting";
}

void zedboardClient::errorOccurred(QAbstractSocket::SocketError socketError)
{
    qDebug()<<"On Error";
    emit statMessage("On Error");
    if(socketError==QAbstractSocket::ConnectionRefusedError)
    {
        reconnectBoard();
    }
}

void zedboardClient::readChannelFinished()
{

    qDebug()<<"On readChannelFinished";

}

// Read from channel
qint64 zedboardClient::readytoRead()
{
    receivedBytes = socket.bytesAvailable();
    incomingBytes.append(socket.read(receivedBytes));
    if(incomingBytes.size() < (int)totalBytes)
    {
        return 0;
    }

    // at this point we have enough data to form a frame
    QByteArray incomingSlice(incomingBytes.data(), totalBytes);
    incomingBytes.remove(0, totalBytes); //remove part extracted

    // Form image from received data
    QImage image((uchar *)incomingSlice.data(), imgWidth,imgHeight,QImage::Format_RGB32);   // use the overloaded constructor

    //Emit the image to the signal
    emit imageReady(image);
    emit statMessage("receiving Image");

    // Prepare the url,
            QUrl url("C:/Users/c.eguzo/Desktop/C-EGUZO-PHD-FZ/GENERAL/Udacity_project/zedboardReceiver/image.png");

    //        // Get the path,
            QString path = url.path();

    //        // Save the image,
            image.save(path,"png");

    return 0;

}


qint64 zedboardClient::processReceivedData(qint64 receivedBytes)
{
    return receivedBytes;
}

void zedboardClient::reconnectBoard()
{
//      networkTimer.singleShot(100, this, SLOT(connectBoard()));
}
