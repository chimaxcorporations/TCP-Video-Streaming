/*This program implements a user interface
 * 1. It provides an interface for connecting the client to network
 * 2. It structures the received data stream
 * 3. It display the data as image on the GUI
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <thread>
#include <chrono>
#include <QLayout>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent),ui(new Ui::MainWindow)
{

    ui->setupUi(this);
}

// Class destructor
MainWindow::~MainWindow()
{
    delete ui;
}

QVideoWidget *MainWindow::getVideo()
{
    return this->player;
}
//Establish connection to client and display status
void MainWindow::on_connectButton_clicked()
{

   if (!signalConnected)
   {       
       ipAdd = ui->ipAddress->text();
       portNum = (ui->portNumber->text()).toUInt();
       connectCode = ui->codeNumber->text();
       client = new zedboardClient(ipAdd, portNum);
       connect(client, &zedboardClient::statMessage, this,&MainWindow::statMessage);
       connect(client, &zedboardClient::imageReady, this, &MainWindow::displayImage); //connect signal to slot
       client->connectBoard();
//       ui->statusDisplay->setText("Connected");
       signalConnected = true;
    }
   else
   {
     ui->statusDisplay->append("Clicked Already");
   }

}

void MainWindow::on_disconnectButton_clicked()
{
    ui->ipAddress->clear();
    ui->portNumber->clear();
    ui->codeNumber->clear();
    client->disconnectBoard();
//    ui->statusDisplay->setText("Disconnected");
    ui->imgFrame->setText("Socket Closed");
    signalConnected = false;
}
// Display image on Label
void MainWindow::displayImage(QImage image)
{
    QImage img= image.copy();
    if(!img.isNull())
    {
        ui->imgFrame->setPixmap(QPixmap::fromImage(img));
    }
    else
    {
        ui->imgFrame->setText("Null Image");
        ui->statusDisplay->setText("Null Image received");
    }

}

void MainWindow::statMessage(QString statMsg)
{
    QString stat = statMsg;
    ui->statusDisplay->setText(stat);
}



