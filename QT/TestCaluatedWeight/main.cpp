#include "widget.h"
#include <QApplication>
#include <QWSServer>

#include <QTextCodec>
int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QApplication::setOverrideCursor(Qt::BlankCursor);

  QWSServer::setCursorVisible(false);
  QTextCodec *codec = QTextCodec::codecForName("utf-8");
  QTextCodec::setCodecForLocale(codec);
  QTextCodec::setCodecForCStrings(codec);
  QTextCodec::setCodecForTr(codec);


  Widget w;

  w.show();

  return a.exec();
}
