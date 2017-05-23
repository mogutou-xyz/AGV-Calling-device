#include <QtGui/QApplication>
#include "widget.h"
#include <QTextCodec>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

    QFontDatabase::addApplicationFont(":image/wqy-microhei.ttf");
    Widget* w = Widget::NewAGV_Calling_device();
    int ret = -1;
    if(w != NULL)
    {   w->setFont(QFont("microhei",30,QFont::Normal));
        w->show();
        ret = a.exec();
    }
    delete w;
    
    return ret;
}
