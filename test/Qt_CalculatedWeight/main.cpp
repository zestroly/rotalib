#include "widget.h"
#include <QApplication>
#include <QTextCodec>


int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  QApplication::setOverrideCursor(Qt::BlankCursor);

  QTextCodec *codec = QTextCodec::codecForName("utf-8");
  QTextCodec::setCodecForLocale(codec);
  QTextCodec::setCodecForCStrings(codec);
  QTextCodec::setCodecForTr(codec);

  Widget w;
  w.setWindowTitle("你好！");
  w.show();

  return a.exec();
}
