#include "widget.h"
#include "ui_widget.h"
#include "ui_ipsetting.h"
#include "ZNetWork.h"
#include "ZWifiMananger.h"
#include "ZSystemIO.h"
#include <QDebug>
#include <QApplication>
#include <QProcess>
#include <calibration.h>
#include <QFile>
#include <dramview.h>
#include "ZBluetooth.h"

#include <QMessageBox>
#include <QTimer>
Widget::Widget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::Widget),wifimananger(NULL)
{
 ui->setupUi(this);

//  Ui::Form *u1 = new Ui::Form;
//  u1->setupUi(this);
    this->showFullScreen();

    wifimananger = new A7::ZWifiMananger;

    ui->WifiScan->setDisabled(true);
    ui->WifiSetting->setDisabled(true);
    ui->WifiSSID->setDisabled(true);
    ui->WIFIPASS->setDisabled(true);

    DramView* dv = new DramView(this);
    ui->tabWidget->addTab(dv,"画布");
    ui->tabWidget->setCurrentWidget(dv);
    dv->setFocusPolicy(Qt::ClickFocus);
    dv->setFocus();

}

void Widget::OnTimerOut()
{
  //hello
  qDebug()<<"screen off";
}

bool Widget::notify(QObject* obj,QEvent* e)
{
  if(e->type() == QEvent::MouseMove)
  {
    qDebug()<<"2";

  }else{
    qDebug()<<"1";

  }
  return true;
//  return QApplication::notify(obj, e);
}


Widget::~Widget()
{

  delete wifimananger;

  delete ui;
}

#if 0
void Widget::on_pushButton_clicked()
{
  A7::ZNetWorkBase::TNetWorkInfo nwf;
  nwf.mothod = A7::ZNetWorkBase::STATIC;
  nwf.ipaddress="192.168.2.80";
  nwf.gateway="192.168.2.1";
  nwf.subnetmask="255.255.255.0";
  nwf.dns= "192.168.2.1";

  A7::ZNetWork network("eth0");
  network.setNetWork(nwf);
}

void Widget::on_pushButton_2_clicked()
{
  A7::ZNetWorkBase::TNetWorkInfo nwf;
  A7::ZNetWork network("eth0");
  network.getNetWork(nwf);
  qDebug()<<""<< ( nwf.mothod == A7::ZNetWorkBase::STATIC?"static":"dhcp"  );
  qDebug()<<"ipaddress" <<nwf.ipaddress.c_str();
  qDebug()<<"gateway" <<nwf.gateway.c_str();
  qDebug()<<"subnetmask" <<nwf.subnetmask.c_str();
  qDebug()<<"dns" <<nwf.dns.c_str();
}
#endif






void Widget::on_WifiScan_clicked()
{
    ui->WifiSSID->clear();
    wifis.clear();
    wifimananger->WifiScaning(wifis) ;
    for(auto wifi: wifis)
    {
      ui->WifiSSID->addItem(QString(wifi.ssid.c_str()));
      qDebug()<<wifi.ssid.c_str()<<wifi.signal.c_str()
            <<wifi.bssid.c_str()<<wifimananger->EncrypTostring(wifi.encryp).c_str();
    }
}

void Widget::on_Wifi_switch_clicked()
{
  if(ui->Wifi_switch->text() == "Wifi开")
  {
      ui->WifiScan->setDisabled(false);
      ui->WifiSetting->setDisabled(false);
      ui->WifiSSID->setDisabled(false);
      ui->WIFIPASS->setDisabled(false);

      wifimananger->setWifi(A7::ZWifiMananger::ON);
      ui->Wifi_switch->setText("Wifi关");
  }else{
      ui->WifiScan->setDisabled(true);
      ui->WifiSetting->setDisabled(true);
      ui->WifiSSID->setDisabled(true);
      ui->WIFIPASS->setDisabled(true);

      wifimananger->setWifi(A7::ZWifiMananger::OFF);
      ui->Wifi_switch->setText("Wifi开");
  }
}

void Widget::on_WifiSetting_clicked()
{
  std::string ssid = ui->WifiSSID->currentText().toStdString();
  std::string password = ui->WIFIPASS->text().toStdString();
  qDebug()<<"will connect:"<<ssid.c_str()<<":"<<password.c_str();
  for(auto wifi: wifis)
  {
    if(wifi.ssid == ssid)
    {
        wifimananger->connectWifi(wifi.ssid,password, wifi.encryp);
    }
  }
}

void Widget::on_pushButtonSocketWifiStatus_clicked()
{
  std::string ret;
  ret = wifimananger->WifiStatus();
  qDebug("[%s]", ret.c_str());

}

void Widget::on_pushButton_clicked()
{

  if(ui->lineEdit->text() != "")
  {
      std::list<std::string> pidlist;
      A7::ZSystemIO::getProgressPid(ui->lineEdit->text().toStdString(), pidlist);
      ui->comboBox_2->clear();
      for(auto l: pidlist)
      {
          ui->comboBox_2->addItem(QString(l.c_str()));
      }

  }
}

void Widget::on_pushButton_2_clicked()
{
    QString pidstr = ui->comboBox_2->currentText() ;
    if(pidstr != "")
    {
        bool ok;
        pid_t pid= pidstr.toInt(&ok);
        if(ok)
            A7::ZSystemIO::killProgressByPid(pid);
        on_pushButton_clicked();
    }

}

void Widget::on_pushButton_3_clicked()
{
  A7::ZWifiMananger::TStatus status = wifimananger->getWifi();
  if(status == A7::ZWifiMananger::ON)
    qDebug()<<"wifi is ON!";
  else
    qDebug()<<"wifi is OFF!";


}

void Widget::on_pushButton_4_clicked()
{

  std::list<A7::ZWifiMananger::TApNode> Aplist;
  wifimananger->wpa_cli_list_network(Aplist);

}

void Widget::on_pushButtonSocketWifiStatus_2_clicked()
{
  std::string ssid = ui->WifiSSID->currentText().toStdString();
  std::string password = ui->WIFIPASS->text().toStdString();
  for(auto wifi: wifis)
  {
    if(wifi.ssid == ssid)
    {
        wifimananger->saveWifiToConfigFile(wifi.ssid,password, wifi.encryp);
    }
  }
}

void Widget::on_pushButtonSocketWifiStatus_3_clicked()
{

 wifimananger->wifi_json_To_Wpa_supplicant_conf();
}

void Widget::on_pushButton_5_clicked()
{
 // system("ts_calibrate &");
}

void Widget::on_pushButton_6_clicked()
{
  qDebug()<<"Calibration start ...";
  Calibration cal;
  cal.exec();
  qDebug()<<"Calibration end ...";

  QMessageBox::StandardButton rb = QMessageBox::information(NULL, "Title", "Content", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
  if(rb == QMessageBox::Yes)
  {
    qDebug()<<"save to pointeral";
    QFile rfile("/opt/qt_pointercal");
    if(rfile.open(QIODevice::ReadOnly))
    {
      QString data;
      char buff[512];
      rfile.readLine(buff, 512);
      data=buff;
      qDebug()<<data;

      QFile wfile("/opt/pointercal");
      wfile.open(QIODevice::WriteOnly);
      wfile.write(data.toLatin1(), data.length());
      wfile.close();

      rfile.close();
    }

  }
}

void Widget::on_pushButton_7_clicked()
{
  std::map<std::string, std::string> devs;
  A7::ZBluetooth bt;
  bt.scan(devs);

  for(auto dev : devs)
  {
    qDebug()<<dev.first.c_str()<<"|"<<dev.second.c_str();

  }


}
