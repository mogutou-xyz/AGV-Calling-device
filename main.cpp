#include <QtGui/QApplication>
#include "widget.h"
#include <QTextCodec>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

    Widget* w = Widget::NewAGV_Calling_device();
    int ret = -1;
    if(w != NULL)
    {   w->setFont(QFont("unifont",18,QFont::Normal));
        w->show();
        ret = a.exec();
    }
    delete w;
    
    return ret;
}
