#include "udpserver.h"

udpServer::udpServer(QString serverIP, int serverPort, QObject *parent) : QObject(parent)
{
    // Default initialization of computer's IP (set manually to IP displayed by ifconfig (in terminal))
    m_serverIP = serverIP; // example : "192.168.0.100"
    // Default port
    m_serverPort = serverPort;

    // assign a qudp socket to this object
    m_serverSocket = new QUdpSocket(this);
    // bind server to specified IP address and port
    m_serverSocket->bind(QHostAddress(serverIP), serverPort, QUdpSocket::DefaultForPlatform);

    // connect 'message-available' signal of qudpserver to this class's responder slot
    connect(m_serverSocket, SIGNAL(readyRead()), this, SLOT(responder()) );

}


void udpServer::responder(){

    //a client is available since a message was received from it
    m_clientAvailable = true;

    // for storing datagram received from incoming client (uDATAGRAMp)
    QByteArray receivedDatagram;
    // resize bytearray to size of pending datagram
    receivedDatagram.resize(m_serverSocket->pendingDatagramSize());
    // read the pending datagram
    m_serverSocket->readDatagram(receivedDatagram.data(), receivedDatagram.size(), &m_clientaddress, &m_clientport);

    //
    qDebug() << "Received message : " << receivedDatagram.data();
    qDebug() << "Sending client's port : " << m_clientport;
    qDebug() << "Sending client's IP address : " << m_clientaddress.toString();

    // Send back an acknowledgment
    QByteArray messageToSend;
    messageToSend.append("Hi there, XAware's udpServer received your message.");
    m_serverSocket->writeDatagram(messageToSend, m_clientaddress, m_clientport);
}


void udpServer::setMessage(QString message){
    m_message = message;

    qDebug() << "New message was set : ";
    qDebug() << m_message;
}


void udpServer::sendmessageToClient(){
        qDebug() << "Sending message to client ...";
        qDebug() << "At IP address : " << m_clientaddress.toString();
        qDebug() << "Port : " << m_clientport;

        QByteArray messageToSend;
        messageToSend.append(m_message);
        m_serverSocket->writeDatagram(messageToSend, m_clientaddress, m_clientport);

}

// get message to be sent to client
QString udpServer::getMessage() const{
    return m_message;
}

// get server port
int udpServer::getServerPort() const{
    return m_serverPort;
}

// set server port
bool udpServer::setServerPort(const int port){
    m_serverPort = port;
    m_serverSocket->disconnectFromHost();
    return m_serverSocket->bind(QHostAddress(m_serverIP), m_serverPort, QUdpSocket::DefaultForPlatform);

}

// get server IP
QString udpServer::getServerIP() const{
    return m_serverIP;
}

// set server IP
bool udpServer::setServerIP(QString IP){
    m_serverIP = IP;
    m_serverSocket->disconnectFromHost();
    return m_serverSocket->bind(QHostAddress(m_serverIP), m_serverPort, QUdpSocket::DefaultForPlatform);
}

// get current client IP
QString udpServer::getClientIP(){
    return m_clientaddress.toString();
}

// set current client IP
bool udpServer::setClientIP(QString clientIP){
    m_clientaddress = clientIP;
    return true;
}

// check if client available
bool udpServer::isClientAvailable(){
    return m_clientAvailable;
}
