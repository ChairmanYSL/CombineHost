#include "tcpserver.h"

TCPServer::TCPServer(QObject *parent)
    : QObject(parent), m_clientSocket(nullptr)
{
    m_clientSocket = new QTcpSocket(this);

    connect(&m_server, &QTcpServer::newConnection, this, &TCPServer::handleNewConnection);
    connect(m_clientSocket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),this, &TCPServer::handleError);}

void TCPServer::listen(const QString &hostAddress, quint16 port)
{
    // 监听TCP端口
    m_server.listen(QHostAddress(hostAddress), port);
    qDebug() << "TCP server listening on" << hostAddress << "port" << port;
}

int TCPServer::sendData(const QByteArray &data)
{
    if (m_clientSocket)
    {
        // 发送TCP数据
       return m_clientSocket->write(data);
    }
}

void TCPServer::closeConnection()
{
    if (m_clientSocket)
    {
        // 关闭TCP连接
        m_clientSocket->close();
        m_clientSocket->deleteLater();
        m_clientSocket = nullptr;
    }
}

void TCPServer::handleNewConnection()
{
    // 获取新连接的客户端套接字
    m_clientSocket = m_server.nextPendingConnection();

    // 连接TCP缓存可读的信号到槽函数
    connect(m_clientSocket, &QTcpSocket::readyRead, this, &TCPServer::handleReadyRead);
}

void TCPServer::handleReadyRead()
{
    if (m_clientSocket)
    {
        // 读取TCP缓存中的数据
        QByteArray data = m_clientSocket->readAll();

        // 发送数据处理信号
        emit dataReceived(data);
    }
}

void TCPServer::handleError(QAbstractSocket::SocketError socketError)
{
    QString errorMessage = m_clientSocket->errorString();
    emit errorOccurred(socketError, errorMessage);
    qDebug() << "TCP error occurred:" << socketError;
    qDebug() << "Error message:" << m_clientSocket->errorString();
}

void TCPServer::clearBuffer()
{
    m_clientSocket->readAll(); // 读取并丢弃已接收的数据
    m_clientSocket->waitForReadyRead(1); // 等待 1ms 确保缓存已清空
}

bool TCPServer::isServerListening()
{
    return m_server.isListening();
}

bool TCPServer::isSocketOpen()
{
    return m_clientSocket->isOpen();
}
