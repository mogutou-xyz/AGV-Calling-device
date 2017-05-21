#include "network.h"
#include <QDebug>


network::network(const QString & hostName, quint16 port,int heattime,QObject *parent) :
    QThread(parent)
{
    m_ThreadClose = false;
    m_hostName = hostName;
    m_port = port;
    m_timerMsec = heattime;
    NewConnect();
    connect(&m_tcpsocket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(DisplayERR(QAbstractSocket::SocketError)));
    connect(&m_tcpsocket,SIGNAL(readyRead()),this,SLOT(GetHeartbeat()));
    connect(&m_timer,SIGNAL(timeout()),this,SLOT(Timeout()));
    connect(&m_tcpsocket,SIGNAL(disconnected()),this,SLOT(Disconnect()));
    connect(this,SIGNAL(LinkClose()),this,SLOT(NewConnect()));
    start();
}

bool network::Construct()
{
    bool ret = true;
    return ret;
}

void network::NewConnect()
{
    m_tcpsocket.close();
    m_tcpsocket.connectToHost(m_hostName,m_port);
    if (m_tcpsocket.waitForConnected(1000))
    {
        qDebug("Connected!");
        m_linkisTrue = true;
        m_timer.start(m_timerMsec);
        qDebug()<< m_tcpsocket.state();
    }
    else
    {
        m_linkisTrue = false;
    }
}

void network::DisplayERR(QAbstractSocket::SocketError)
{
    qDebug()<< m_tcpsocket.errorString();
}

void network::GetHeartbeat()
{
    qDebug() << "GetHeartbeat";
    m_timer.start(m_timerMsec);
}

void network::Timeout()
{
    qDebug()<< "timeout";
    m_linkisTrue = false;
}

void network::Disconnect()
{
    sleep(1);
    qDebug()<< "perr disconnect";
    m_linkisTrue = false;
}

network *network::Newnetwork(const QString & hostName, quint16 port,int heattime)
{
    qDebug()<< "new connect";
    network* ret = new network(hostName,port,heattime);
    if( !(ret && ret->Construct()))
    {
       delete ret;
       ret = NULL;
    }
    return ret;
}

bool network::PutChar(char c)
{
    return m_tcpsocket.putChar(c);
}

void network::Close()
{
    m_tcpsocket.close();
    if (m_tcpsocket.state() == QAbstractSocket::UnconnectedState ||
             m_tcpsocket.waitForDisconnected(1000))
             qDebug("Disconnected!");
}


network::~network()
{
    disconnect(&m_tcpsocket,SIGNAL(disconnected()),this,SLOT(Disconnect()));
    m_linkisTrue = true;
    m_ThreadClose = true;
    wait();
    m_tcpsocket.close();
}

void network::run()
{
    while(m_ThreadClose == false)
    {
          sleep(1);
        if(m_linkisTrue == false)
        {
            emit LinkClose();
        }
    }
}

