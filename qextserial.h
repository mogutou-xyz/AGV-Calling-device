#ifndef QEXTSERIAL_H
#define QEXTSERIAL_H

#include <QObject>
#include <QString>
#include "qextserialport.h"

class QextSerial : public QObject
{
    Q_OBJECT
    char m_station_number;

    QString m_portname;
    quint8 m_message[6];
    QextSerialPort *m_port;
    quint8 LRC(const quint8* src,quint32 len);
    void PackMessage();

    QextSerial(const QString &portname,char stationNumber,QObject *parent = 0);
    bool Construct();
public:
    static QextSerial* NewQextSerial(const QString &portname,char stationNumber);
    ~QextSerial();
    void onSend();
    void onPutchar();
signals:
    void getBack();
private  slots:

    void onReadyRead();
    void onDsrChanged(bool status);
    
};

#endif // QEXTSERIAL_H
