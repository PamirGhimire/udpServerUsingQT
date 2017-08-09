#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "udpserver.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    // create an instance of the udp server
    udpServer* server;

private slots:
    void on_pushButton_clicked();

    void on_sendmessage_clicked();

    void on_changeip_clicked();

    void on_changeport_clicked();

private:
    Ui::MainWindow *ui;

signals:
    void sendMessage_pushbutton_pressed();
};

#endif // MAINWINDOW_H
