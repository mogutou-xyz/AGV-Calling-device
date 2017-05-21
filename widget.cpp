#include "widget.h"
#include <QIcon>
#include <QSize>
#include <QInputDialog>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QDataStream>
#include <QDir>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QString>
#include <QtGui/QApplication>
#include <QDesktopWidget>
#include <QDialogButtonBox>
#include <QDialog>
#include <configdialog.h>

Widget::Widget(QWidget *parent)
    : QWidget(parent),configBtn(this),openCallingBtn(this)
{
    initUI();

    connect(&configBtn,SIGNAL(clicked()),this,SLOT(Config_station_number()));
    connect(&openCallingBtn,SIGNAL(clicked()),this,SLOT(Open_CallingDevice()));
}

bool Widget::Construct()
{
    bool ret = true;
    return ret;
}

bool Widget::initUI()
{
    bool ret = true;
    setWindowFlags(Qt::FramelessWindowHint);
    QGridLayout* gLayout = new QGridLayout(this);
    configBtn.setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    configBtn.setIcon(QIcon(":/image/PNG114.png"));
    configBtn.setIconSize(QSize(150,150));

    configBtn.setText(tr("配置工位号"));
    configBtn.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    openCallingBtn.setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    openCallingBtn.setIcon(QIcon(":/image/PNG102.png"));
    openCallingBtn.setIconSize(QSize(150,150));

    openCallingBtn.setText(tr("打开呼叫器"));
    openCallingBtn.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);  


    gLayout->addWidget(&configBtn,0,0);
    gLayout->addWidget(&openCallingBtn,0,1);

    resize(QApplication::desktop()->width(),QApplication::desktop()->height());
    return ret;
}

Widget *Widget::NewAGV_Calling_device()
{
    Widget* ret = new Widget();

       if( !(ret && ret->Construct()) )
       {
           delete ret;
           ret = NULL;
       }
       return ret;
}

Widget::~Widget()
{

}

void Widget::Config_station_number()
{   
    COnfigDialog ConfigDlg;
    if(1 == ConfigDlg.exec())
    {
        QFile file(QDir::currentPath()+ "/station_number.txt");
        if( file.open(QIODevice::WriteOnly | QIODevice::Text) )
        {
                QTextStream out(&file);
                out << ConfigDlg.getInt();
                file.close();
        }
    }
}

void Widget::Open_CallingDevice()
{

    QFile file(QDir::currentPath()+ "/station_number.txt");
    if( file.open(QIODevice::ReadOnly | QIODevice::Text) )
    {

        QTextStream in(&file);

        while( !in.atEnd() )
        {

            station_number = in.readAll().toInt();

            Workstation* workstation =  Workstation:: NewWorkstation( station_number);
            if(workstation!= NULL)
            {
                workstation->exec();
                delete workstation;
            }
        }
        file.close();

    }

}
