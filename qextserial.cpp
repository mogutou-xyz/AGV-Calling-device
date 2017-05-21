#include "qextserial.h"
#include <QByteArray>
#include <QDebug>

QextSerial::QextSerial(const QString &portname,char stationNumber,QObject *parent) :
    QObject(parent)
{

    m_station_number = stationNumber;
    m_portname = portname;
    PackMessage();
}

bool QextSerial::Construct()
{
    bool ret = true;
    m_port = new QextSerialPort(m_portname,QextSerialPort::EventDriven);
    if(m_port != NULL)
    {

        m_port->setBaudRate(BAUD9600);
        m_port->setDataBits(DATA_8);
        m_port->setStopBits(STOP_1);
        m_port->setParity(PAR_NONE);
        m_port->setFlowControl(FLOW_OFF);
        if(true == m_port->open(QIODevice::ReadWrite))
        {
            qDebug()<< "serial port  oK";
            connect(m_port,SIGNAL(readyRead()),this,SLOT(onReadyRead()));
            connect(m_port,SIGNAL(dsrChanged(bool)),this,SLOT(onDsrChanged(bool)));
        /*    if(!(m_port->lineStatus() & LS_DSR))
            {
                qDebug()<< "warning: device is not turned on";
            }
            */
        }
        else
        {
            qDebug()<< "device failed to open:" << m_port->errorString();
            ret = false;           
            delete m_port;
            m_port = NULL;
        }
    }
    else
    {
        ret = false;
    }

    return ret;
}

QextSerial *QextSerial::NewQextSerial(const QString &portname, char stationNumber)
{
    QextSerial* ret = new QextSerial(portname,stationNumber);

    if(!(ret && ret->Construct()))
    {
       delete ret;
       ret = NULL;
    }
    return ret;
}

QextSerial::~QextSerial()
{ 
    if(m_port != NULL)
    {
        m_port->close();
        delete m_port;
        m_port = NULL;
    }
}

void QextSerial::onSend()
{

    const QByteArray message(reinterpret_cast<const char*>(m_message),sizeof(m_message));
    m_port->write(message);
}

void QextSerial::onPutchar()
{

    const QByteArray message(1,m_station_number);
    m_port->write(message);
}

void QextSerial::onReadyRead()
{

    int a = m_port->bytesAvailable();
    char buf = 0;
    m_port->read(reinterpret_cast<char*>(&buf),a);
    //qDebug()<<"read :"+ QString::number(buf);
    if(buf == 0x01)
    {

        emit getBack();
    }
}

void QextSerial::onDsrChanged(bool status)
{
    qDebug()<<"onDsrChanged";
}

quint8 QextSerial::LRC(const quint8* src, quint32 len)
{
    quint8 lrc = 0;
    for(quint32 i = 0;i<len;i++)
    {
        lrc += src[i];
    }
    lrc = (~lrc)+1;
    return lrc;
}

void QextSerial::PackMessage()
{
    m_message[0] = 0x55;
    m_message[1] = m_station_number;
    m_message[2] = 0x00;
    m_message[3] = 0x00;
    m_message[4] = LRC(m_message+1,3);
    m_message[5] = 0xaa;
}
