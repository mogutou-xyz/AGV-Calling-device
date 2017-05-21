#include "workstation.h"
#include <QDebug>
#include <QString>
#include <QIcon>
#include <QPixmap>
#include <QBitmap>
#include <QDesktopWidget>
#include <QtGui/QApplication>
#include <QTextCodec>

Workstation::Workstation( char number,QDialog *parent) :
    QDialog(parent),stateBtn(this),CompleteBtn(this)
{  

    station_number = number;
    initUI();
    connect(&ledBtn,SIGNAL(clicked()),this,SLOT(close()));
    connect(&CompleteBtn,SIGNAL(clicked()),this,SLOT(onLackMaterialBtnClicked()));
}

bool Workstation::initUI()
{
    bool ret =true;
    setWindowFlags(Qt::FramelessWindowHint);
    label.setText(tr("AGV呼叫器"));
    label.setFont(QFont("unifont", 50, QFont::Black));

    ledBtn.setStyleSheet("QPushButton{border:0px;}");
    ledBtn.setIcon(QPixmap("image/arrow_left.png"));
    ledBtn.setIconSize(QSize(25,25));
    ledBtn.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    CompleteBtn.setIcon(QPixmap("image/calling.png"));
    CompleteBtn.setIconSize(QSize(25,25));

    stateBtn.setEnabled(false);
    stateBtn.setStyleSheet("QPushButton{border:0px;}");
    //stateBtn.setEnabled(false);
    stateBtn.setText(QString::number(station_number)+"号工位");
    stateBtn.setFont(QFont("unifont", 40, QFont::Bold));
    stateBtn.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    //CompleteBtn.setStyleSheet("QPushButton{border:0px;}");
    CompleteBtn.setIcon(QPixmap("image/calling.png"));
    CompleteBtn.setIconSize(QSize(150,150));
    CompleteBtn.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);


    hlayout.addWidget(&ledBtn,1,Qt::AlignLeft);
    hlayout.addWidget(&label,4,Qt::AlignJustify);
    hlayout.addWidget(&stateBtn,1,Qt::AlignRight);

    vlayout.addLayout(&hlayout);
    vlayout.addWidget(&CompleteBtn);
    vlayout.setStretchFactor(&hlayout,1);
    vlayout.setStretchFactor(&CompleteBtn,6);
    setLayout(&vlayout);

    this->setAttribute(Qt::WA_ShowModal,true);
    resize(QApplication::desktop()->width(),QApplication::desktop()->height());
    return ret;
}

bool Workstation::Construct()
{
    bool ret = true;
    m_SerialPort = QextSerial::NewQextSerial("/dev/ttyUSB0",station_number);
    if(!m_SerialPort)
    {
        qDebug()<< "fail open serial port";
        ret = false;
    }
    else
    {
        connect(m_SerialPort,SIGNAL(getBack()),this,SLOT(onGetBack()));
    }

    return ret;
}

Workstation::~Workstation()
{
    delete m_SerialPort;
}

void Workstation::onLackMaterialBtnClicked()
{
    CompleteBtn.setIcon(QPixmap("image/telephone.png"));
    m_SerialPort->onPutchar();
}

void Workstation::onGetBack()
{
    CompleteBtn.setIcon(QPixmap("image/calling.png"));
}

Workstation *Workstation::NewWorkstation(char number)
{
    Workstation* ret = new Workstation(number);

       if( !(ret && ret->Construct()) )
       {

           delete ret;
           ret = NULL;
       }
       return ret;
}

