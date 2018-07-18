#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMutex>

#include "ZCalculatedWeight.h"
#include "ZSerialPortToSerialPort.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

  public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    static void SerialCallback(A7::ZCalculatedWeight::TWeightPacket& packet, void* pClass);

    void updateLog(QString data);
    void clearLog();

  signals:
    void SendSerialData(QString data);

  private slots:
    void on_pushButton_clicked();
    void RecvSerialData(QString data);

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

  private:
    Ui::Widget *ui;
    A7::ZCalculatedWeight* calweight;
    QMutex mutex;

    A7::ZSerialPortToSerialPort* spts;

    QMutex mutexlog;
};

#endif // WIDGET_H
