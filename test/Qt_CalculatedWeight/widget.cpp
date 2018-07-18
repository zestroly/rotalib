#include "widget.h"
#include <QDebug>
#include <QTime>
#include <QDateTime>

Widget::Widget(QWidget *parent)
  : QWidget(parent)
{

  QWidget::setCursor(QCursor(Qt::BlankCursor));


  this->showFullScreen();

  QFont font = this->font();
  font.setPointSize(30);
  this->setFont(font);

 // this->resize(800,480);
  QPushButton *pushbutton;
  pushbutton =new QPushButton(tr("打开"),this);
  pushbutton->move(30, 30);
  pushbutton->setObjectName(tr("打开"));
  connect(pushbutton, SIGNAL(clicked(bool)),this ,SLOT(recvPushButtonEvent(bool)));
  PushButtons.push_back(pushbutton);

  connect(this, SIGNAL(SendSerialData(QString)), this,SLOT(RecvSerialData(QString)));

  QLabel* label = new QLabel(tr("重量"), this);
  label->move(30, 100);
  label->setObjectName(tr("重量"));
  Labels.push_back(label);

  label = new QLabel(tr("重量向下"), this);
  label->move(400, 100);
  label->setObjectName(tr("重量向下"));
  Labels.push_back(label);

  label = new QLabel(tr("重量向上"), this);
  label->move(600, 100);
  label->setObjectName(tr("重量向上"));
  Labels.push_back(label);

  label = new QLabel(tr("稳定"), this);
  label->move(600, 100);
  label->setObjectName(tr("稳定"));
  Labels.push_back(label);

  label = new QLabel(tr("零点"), this);
  label->move(600, 100);
  label->setObjectName(tr("零点"));
  Labels.push_back(label);


}

void Widget::SerialCallback(uint8_t* buff, int len, void* pClass)
{
  QByteArray array((char*)buff, len);
  QString data(array.toHex());
  emit ((Widget*)pClass)->SendSerialData(data);
}

void Widget::RecvSerialData(QString data)
{
  Log()<<data;

}



void Widget::recvPushButtonEvent(bool status)
{
  QPushButton *pushbutton = dynamic_cast<QPushButton*>(sender());
  if(pushbutton->text()==tr("打开") )
  {
    CalWeight = new A7::ZCalculatedWeight(SerialCallback, this);
    pushbutton->setText("关闭");
  }else{
    delete CalWeight;
    pushbutton->setText(tr("打开"));
  }
}


Widget::~Widget()
{

}
