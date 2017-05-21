#ifndef NETWORK_H
#define NETWORK_H

#include <QThread>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QTimer>


class network : public QThread
{
    Q_OBJECT
    volatile bool m_ThreadClose;
    QTimer m_timer;
    int m_timerMsec;
    QTcpSocket m_tcpsocket;
    QString  m_hostName;
    quint16 m_port;
    bool m_linkisTrue;

    network(const QString & hostName, quint16 port,int heattime,QObject *parent = 0);
    bool Construct();

public:
    static network* Newnetwork(const QString & hostName, quint16 port,int heattime);
    bool PutChar(char c);
    void Close();
    ~network();
protected:
    void run();

signals:
    void LinkClose();
private slots:
    void NewConnect();
    void DisplayERR(QAbstractSocket::SocketError);
    void GetHeartbeat();
    void Timeout();
    void Disconnect();
};

#endif // NETWORK_H
