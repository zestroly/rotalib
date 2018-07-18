#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include "ZWifiMananger.h"




namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

  public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    bool notify(QObject* ,QEvent*);

  private slots:
    void on_WifiScan_clicked();

    void on_Wifi_switch_clicked();

    void on_WifiSetting_clicked();

    void on_pushButtonSocketWifiStatus_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void OnTimerOut();

    void on_pushButtonSocketWifiStatus_2_clicked();

    void on_pushButtonSocketWifiStatus_3_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

  private:
    Ui::Widget *ui;
    A7::ZWifiMananger* wifimananger;

    std::list<A7::ZWifiMananger::TWifi> wifis;
};

#endif // WIDGET_H
