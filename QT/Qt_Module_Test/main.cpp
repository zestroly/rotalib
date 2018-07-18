#include "widget.h"
#include <QApplication>
#include <QWSServer>
#include <QTextCodec>
#include <QDebug>
#include <QWSServer>
#include <QTimer>
#include <stdlib.h>
#include <unistd.h>

#include "Application.h"



int main(int argc, char *argv[])
{
    // QApplication a(argc, argv);
    system("echo \"7\" > /sys/devices/platform/backlight/backlight/backlight/brightness ");

    Application a(argc, argv);
  //  QWSServer::setCursorVisible(false);
    QWSServer::setBackground(QColor(0,0,0,0));
    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);

    Widget w;
    w.show();


    return a.exec();
}
