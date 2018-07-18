#include "widget.h"
#include <QDebug>
#include <QPainter>
#include <QPushButton>
#include <QImage>
#include <QLabel>

Widget::Widget(QWidget *parent)
  : QWidget(parent)
{
    this->showFullScreen();

    QPushButton* button = new QPushButton(tr("取消"), this);
    button->resize(100, 100);
    button->show();
    button->move(this->width()/2, this->height()/2);
    QFont font = button->font();
    font.setPixelSize(40);
    button->setFont(font);
    connect(button, SIGNAL(clicked(bool)), this, SLOT(close()));
    SToS = new A7::ZSerialPortToSerialPort("/dev/ttymxc2", "/dev/ttymxc1");

}


void Widget::paintEvent(QPaintEvent*)
{
#if 0
    QPainter painter(this);
    QLinearGradient linearGradient(0, 0, this->width(),this->height());
    linearGradient.setColorAt(0.0, Qt::red);
    linearGradient.setColorAt(0.2, Qt::black);
    linearGradient.setColorAt(0.4, Qt::yellow);
    linearGradient.setColorAt(0.6, Qt::white);
    linearGradient.setColorAt(0.8, Qt::green);
    linearGradient.setColorAt(1.0, Qt::blue);
    painter.setBrush(linearGradient);
    painter.drawRect(0, 0, this->width(), this->height());
#endif

}


Widget::~Widget()
{
  delete SToS;
  qDebug()<<"exit!";
}
