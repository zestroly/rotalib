#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QDateTime>
#include <QTimer>


Widget::Widget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::Widget),calweight(NULL),spts(NULL)
{
  this->setWindowFlags (Qt::Window | Qt::FramelessWindowHint);
  QTimer::singleShot(0, this, SLOT(showFullScreen()));

  ui->setupUi(this);

  ui->pushButton->setFocusPolicy(Qt::NoFocus);
  ui->pushButton_2->setFocusPolicy(Qt::NoFocus);
  ui->pushButton_3->setFocusPolicy(Qt::NoFocus);
  ui->pushButton_4->setFocusPolicy(Qt::NoFocus);
  ui->tabWidget->setFocusPolicy(Qt::NoFocus);

  connect(this, SIGNAL(SendSerialData(QString)),
          this,SLOT(RecvSerialData(QString)));

  this->showFullScreen();

}

Widget::~Widget()
{
  delete ui;
}

void Widget::SerialCallback(A7::ZCalculatedWeight::TWeightPacket& packet, void* pClass)
{
 // QByteArray array((char*)packet.buffsrc, packet.bufflen);
//  QString data(array.toHex());
  std::string mesg = A7::ZSerialPort::ToHexString(packet.buffsrc, packet.bufflen);
  emit ((Widget*)pClass)->SendSerialData(QString::fromUtf8(mesg.c_str()));
}

void Widget::updateLog(QString data)
{
  QString strtime = QDateTime::currentDateTime().toString("hh:mm:ss.zzz");
  mutexlog.lock();
  this->ui->textEdit->append(strtime+": "+data);
  this->ui->textEdit->moveCursor(QTextCursor::End);
  mutexlog.unlock();
}
void Widget::clearLog()
{
  mutexlog.lock();
  ui->textEdit->clear();
  mutexlog.unlock();
}


void Widget::RecvSerialData(QString data)
{
    // QString strtime = QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss.zzz");
    updateLog(data);

    A7::ZCalculatedWeight::TWeightInfo info;
    info.OutTare = 0.0f;
    info.OutWeight = 0.0f;

    mutex.lock();
    if(calweight != NULL)
        calweight->GetInfo(info);
    mutex.unlock();

    if(info.isAvaliable)
    {
        this->ui->label_3->setText(QString("%1").arg(info.OutWeight));
        this->ui->label_6->setText(QString("%1").arg(info.OutTare));
        this->ui->checkBox_2->setChecked(info.isOnZero);
        this->ui->checkBox->setChecked(info.isStabilize);
        this->ui->checkBox_3->setChecked( info.OutTare > 0.001f ? true:false);
        this->ui->checkBox_4->setChecked( info.isCrossMaxValue);
        this->ui->checkBox_5->setChecked( info.isCrossMinValue);

     //   this->ui->label_8->setText(QString("%1.%1").arg(info.timestamp.tv_sec,info.timestamp.tv_usec));
        this->ui->label_11->setText(QString("%1").arg(info.PacketRate));
    }
}


void Widget::on_pushButton_clicked()
{
    QPushButton *pushbutton = dynamic_cast<QPushButton*>(sender());

    if(ui->pushButton_4->text() == tr("本地模式"))
    {
        if(pushbutton->text()==tr("连接") )
        {
            mutex.lock();
            calweight = new A7::ZCalculatedWeight(SerialCallback, this);
            mutex.unlock();
            ui->pushButton_4->setDisabled(true);
            pushbutton->setText(tr("断开"));
        }else{
            mutex.lock();
            delete calweight;
            calweight = NULL;
            mutex.unlock();
            ui->pushButton_4->setDisabled(false);
            pushbutton->setText(tr("连接"));
        }
    }
}

void Widget::on_pushButton_2_clicked()
{
    if(calweight != NULL)
    {
        mutex.lock();
        calweight->SetTareWeight();
        mutex.unlock();
    }
}

void Widget::on_pushButton_3_clicked()
{
    if(calweight != NULL)
    {
        mutex.lock();
        calweight->SetZeroWeight();
        mutex.unlock();
    }

}

void Widget::on_pushButton_4_clicked()
{
    if(ui->pushButton->text() == tr("连接"))
    {

        if(ui->pushButton_4->text() == tr("转发模式"))
        {
            ui->pushButton_4->setText(tr("本地模式"));
            ui->pushButton->setEnabled(true);

            delete spts;
            spts = NULL;

        }else{
            ui->pushButton_4->setText(tr("转发模式"));
            ui->pushButton->setEnabled(false);
            spts = new A7::ZSerialPortToSerialPort("/dev/ttymxc2", "/dev/ttymxc1");
        }
    }
}

void Widget::on_pushButton_5_clicked()
{
    this->close();
}


void Widget::on_pushButton_6_clicked()
{
    clearLog();
}

void Widget::on_pushButton_7_clicked()
{//秤重复位
    uint8_t buff[4] = {0x02, 0xCF, 0x03, 0x0d};
    mutex.lock();
    if(calweight != NULL)
        calweight->writeData(buff, 4);
    mutex.unlock();


}

void Widget::on_pushButton_8_clicked()
{//不归零修正
    uint8_t buff[4] = {0x02, 0x32, 0x03, 0x0d};
    mutex.lock();
    if(calweight != NULL)
        calweight->writeData(buff, 4);
    mutex.unlock();
}
