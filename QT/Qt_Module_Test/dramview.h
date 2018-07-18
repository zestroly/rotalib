#ifndef DRAMVIEW_H
#define DRAMVIEW_H

#include <QWidget>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QPushButton>

class DramView : public QWidget
{
    Q_OBJECT
  public:
    explicit DramView(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent* event);

  protected:
   // bool event(QEvent *event);

  signals:

  public slots:
  private:
    QPixmap _pix;
    QPixmap _tempPix;
    QPoint _lastPoint;
    QPoint _endPoint;
    qreal _scale;
    bool _isDrawing;


};

#endif // DRAMVIEW_H
