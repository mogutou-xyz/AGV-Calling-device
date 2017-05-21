#include "configdialog.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include <QDebug>
COnfigDialog::COnfigDialog()
{
    setFont(QFont("unifont",100,QFont::Normal));
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowTitle(tr("请选择工位置号："));
    OKBtn.setEnabled(false);
    m_ret = 0;
    textEdit.setReadOnly(true);
    QGridLayout* glayout = new QGridLayout();
    QVBoxLayout* vlayout = new QVBoxLayout(this);
    for(int i=0;i<8;i++)
    {
        pushBtn[i].setText(QString::number(i+1));
        glayout->addWidget(&pushBtn[i],i/4,i%4);
    }
    CloseBtn.setText(tr("取消"));
    OKBtn.setText(tr("确认"));
    glayout->addWidget(&CloseBtn,2,0);
    glayout->addWidget(&OKBtn,2,3);

    vlayout->addWidget(&textEdit);
    vlayout->addSpacing(20);
    vlayout->addLayout(glayout);

    for(int i = 0;i<8;i++)
    {
        connect(&pushBtn[i],SIGNAL(clicked()),this,SLOT(ongetPushBtnValue()));
    }

    connect(&CloseBtn,SIGNAL(clicked()),this,SLOT(close()));
    connect(&OKBtn,SIGNAL(clicked()),this,SLOT(onOKBtn()));
}

int COnfigDialog::getInt()
{
    return m_ret;
}

void COnfigDialog::ongetPushBtnValue()
{
    OKBtn.setEnabled(true);
    QPushButton* btn = dynamic_cast<QPushButton*>(sender());
    textEdit.setText(btn->text());
}

void COnfigDialog::onOKBtn()
{
    m_ret = textEdit.text().toInt();
    done(1);
}
