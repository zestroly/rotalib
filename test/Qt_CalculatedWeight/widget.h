#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QQueue>
#include <QList>
#include <QPushButton>

#include "ZCalculatedWeight.h"

#define Log() qDebug()<<QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss.zzz ").toStdString().c_str()
class Widget : public QWidget
{
    Q_OBJECT

  public:
    Widget(QWidget *parent = 0);
    ~Widget();
    static void SerialCallback(uint8_t* buff, int len, void* pClass);

    signals:
    void SendSerialData(QString data);

  public slots:
    void RecvSerialData(QString data);
    void recvPushButtonEvent(bool);
  private:
    QList<QLabel*> Labels;
    QList<QPushButton*> PushButtons;
    QList<QLineEdit*> LineEdits;
    A7::ZCalculatedWeight* CalWeight;
};

#endif // WIDGET_H
