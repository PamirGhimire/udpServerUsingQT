#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <QObject>
#include<QUdpSocket>
#include<string>

class udpServer : public QObject
{
    Q_OBJECT
private:


    // Client side variables:
    // These pertain to the client from which the server received its latest message

    // Port on which client is listening, to be retrieved upon succesful connection (ex : hololens is a client)
    quint16 m_clientport;
    // IP address of client, to be retrieved upon succesful connection
    QHostAddress m_clientaddress;


    // Server side variables:

    // Server Socket object, to be bound with an IP and a port
    QUdpSocket* m_serverSocket;
    // IP of the server, set this to be the same as the computer's IP (find using ifconfig in terminal)
    QString m_serverIP;
    // Port on which the server (this computer) will listen to messages from the client
    int m_serverPort;
    // State : Is true if a client succesfully connected to the server (so that server remembers its IP and port)
    bool m_clientAvailable = false;

    // message to be sent to the client
    QString m_message;


public:
    // default constructor
    explicit udpServer(QString serverIP, int serverPort = 12345, QObject *parent = 0);

    // set message to be sent to client
    void setMessage(const QString message);

    // get message to be sent to client
    QString getMessage() const;

    // get server port
    int getServerPort() const;

    // set server port
    bool setServerPort(const int port);

    // get server IP
    QString getServerIP() const;

    // set server IP
    bool setServerIP(QString IP);

    // get current client IP
    QString getClientIP();

    // set current client IP
    bool setClientIP(QString clientIP);

    // check if client available
    bool isClientAvailable();

signals:

public slots:
    // responds to messages sent by client (handshake function)
    void responder();

    // send set message to available client (client from which latest message was received)
    void sendmessageToClient();
};

#endif // UDPSERVER_H
