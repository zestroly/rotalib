#ifndef WIDGET_H
#define WIDGET_H

#include "ZSerialPortToSerialPort.h"
#include <QWidget>

class Widget : public QWidget
{
    Q_OBJECT

  public:
    Widget(QWidget *parent = 0);
    ~Widget();
    void paintEvent(QPaintEvent*);
  private:
    A7::ZSerialPortToSerialPort* SToS;
};

#endif // WIDGET_H
