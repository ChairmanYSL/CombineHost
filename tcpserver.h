#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>

class TCPServer : public QObject
{
    Q_OBJECT
public:
    explicit TCPServer(QObject *parent = nullptr);
    void listen(const QString &hostAddress, quint16 port);

       // 发送TCP数据
    int sendData(const QByteArray &data);

       // 关闭TCP连接
    void closeConnection();

    void clearBuffer();

    bool isServerListening();
    bool isSocketOpen();

private slots:
    // 处理新连接
    void handleNewConnection();

    // 处理TCP缓存可读的信号
    void handleReadyRead();
    void handleError(QAbstractSocket::SocketError socketError);

signals:
    void dataReceived(const QByteArray &data);
    void errorOccurred(QAbstractSocket::SocketError socketError, const QString &errorMessage);

private:
    QTcpServer m_server;
    QTcpSocket *m_clientSocket;

};

#endif // TCPSERVER_H
