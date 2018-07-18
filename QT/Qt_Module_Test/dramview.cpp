#include "dramview.h"
#include <QDebug>
#include <QLineEdit>
#include <QTextEdit>
#include <QPainter>

DramView::DramView(QWidget *parent) : QWidget(parent)
{
 // QLineEdit* le = new QLineEdit(this);
  QTextEdit *te = new QTextEdit(this);

//    grabKeyboard();
  this->resize(791,431);
  _pix = QPixmap(this->width(), this->height());
  _pix.fill(Qt::blue);
  _isDrawing = false;
}

void DramView::paintEvent(QPaintEvent *event)
{
  int x,y,w,h;
   x = _lastPoint.x();
   y = _lastPoint.y();
   w = _endPoint.x() - x;
   h = _endPoint.y() - y;
   QPainter painter(this);
   if(_isDrawing) //如果正在绘图，就在辅助画布上绘制
   {
      //将以前pix中的内容复制到tempPix中，保证以前的内容不消失
      _tempPix = _pix;
      QPainter pp(&_tempPix);
      pp.drawRect(x,y,w,h);
      painter.drawPixmap(0, 0, _tempPix);
   } else {
      QPainter pp(&_pix);
      pp.drawRect(x,y,w,h);
      painter.drawPixmap(0,0,_pix);
   }
}

void DramView::mousePressEvent(QMouseEvent *event)
{
  if(event->button()==Qt::LeftButton) //鼠标左键按下
     {
        _lastPoint = event->pos();
        _isDrawing = true;   //正在绘图
     }
}

void DramView::mouseMoveEvent(QMouseEvent *event)
{
     update();
}

void DramView::mouseReleaseEvent(QMouseEvent *event)
{
  if(event->button() == Qt::LeftButton) //鼠标左键释放
  {
     _endPoint = event->pos();
     _isDrawing = false;    //结束绘图
     update();
  }
}

void DramView::keyPressEvent(QKeyEvent *event)
{
  qDebug()<<event->key();


}

#if 0
bool DramView::event(QEvent *event)
{
  if(event->type() == QEvent::TouchBegin){   qDebug()<<"begin";         }
  if(event->type() == QEvent::TouchUpdate){       qDebug()<<"update";        }
  if(event->type() == QEvent::TouchEnd){      qDebug()<<"end";         }
  if (event->type() == QEvent::Gesture) { return true; }
  return QWidget::event(event);
}
#endif


