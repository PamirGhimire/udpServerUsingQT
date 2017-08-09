#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //server = new udpServer("192.168.0.100", 12345);
    QString serverIP = ui->serverip->toPlainText();
    // Initialize server with chosen IP in the server ip text edit
    server = new udpServer(serverIP);
    // Set server's incoming port to the one chosen in the port text edit
    server->setServerPort(ui->serverport->toPlainText().toInt());

    connect(this, SIGNAL(sendMessage_pushbutton_pressed()), server, SLOT(sendmessageToClient()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

// vestigial! Ignore
void MainWindow::on_pushButton_clicked()
{

}

// send message push button
void MainWindow::on_sendmessage_clicked()
{
    server->setMessage(ui->messagebox->toPlainText());
    emit sendMessage_pushbutton_pressed();
}

// change ip pushbutton
void MainWindow::on_changeip_clicked()
{
    server->setServerIP(ui->serverip->toPlainText());
}

// change server's incoming port
void MainWindow::on_changeport_clicked()
{
    server->setServerPort(ui->serverport->toPlainText().toInt());
}
