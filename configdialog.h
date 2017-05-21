#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H
#include <QPushButton>
#include <QDialog>
#include <QLineEdit>
class COnfigDialog : public QDialog
{
    Q_OBJECT
    int m_ret;
    QLineEdit textEdit;
    QPushButton pushBtn[8];
    QPushButton OKBtn;
    QPushButton CloseBtn;
public:
    explicit COnfigDialog();
    int getInt();
signals:

private slots:
    void ongetPushBtnValue();
    void onOKBtn();
};

#endif // CONFIGDIALOG_H
