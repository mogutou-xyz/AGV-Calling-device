#ifndef WORKSTATION_H
#define WORKSTATION_H

#include <QWidget>
#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include "qextserial.h"

class Workstation : public QDialog
{
    Q_OBJECT

    char station_number;
    QLabel label;
    QextSerial* m_SerialPort;
    QPushButton ledBtn;
    QPushButton stateBtn;
    QPushButton CompleteBtn;
    QVBoxLayout vlayout;
    QHBoxLayout hlayout;
    Workstation(char number,QDialog *parent = 0);
    bool initUI();
    bool Construct();
public:
    static Workstation* NewWorkstation(char number);
    ~Workstation();
private slots:
    void onLackMaterialBtnClicked();
    void onGetBack();
};

#endif // WORKSTATION_H
