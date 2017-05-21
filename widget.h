#ifndef WIDGET_H
#define WIDGET_H

#include <QtGui/QWidget>
#include <QToolButton>
#include <QLabel>
#include "workstation.h"


class Widget : public QWidget
{
    Q_OBJECT

    char station_number;


    QToolButton configBtn;
    QToolButton openCallingBtn;
    Widget(QWidget *parent = 0);
    bool Construct();
    bool initUI();

public:
    static Widget* NewAGV_Calling_device();
    ~Widget();

protected slots:
    void Config_station_number();
    void Open_CallingDevice();

};

#endif // WIDGET_H
