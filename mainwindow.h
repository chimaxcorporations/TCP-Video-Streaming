#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "zedboardclient.h"
#include <QMainWindow>
#include <QImage>
#include <QPixmap>
#include <QVideoWidget>
#include <QTimer>
#include <QObject>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(/*zedboardClient *client, */QWidget *parent = nullptr);
    ~MainWindow();
    QImage image;
    QPixmap pixMap;
    QVideoWidget* getVideo();
private slots:
    void on_connectButton_clicked();
    void on_disconnectButton_clicked();
    void displayImage(QImage image);
    void statMessage(QString statMsg);

private:
    Ui::MainWindow *ui;
    quint16 portNum;
    QString ipAdd;
    QString connectCode;
    QVideoWidget* player = new QVideoWidget;
    qint64 receivedData;
    qint64 dataBuffer=0;
    zedboardClient *client;
    bool signalConnected = false;
};
#endif // MAINWINDOW_H
