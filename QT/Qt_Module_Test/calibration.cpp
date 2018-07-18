/****************************************************************************
**
** Copyright (C) 2014 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "calibration.h"
#include <QDebug>
#include <QLabel>

#include <QWSPointerCalibrationData>
#include <QPainter>
#include <QFile>
#include <QTimer>
#include <QApplication>
#include <QDesktopWidget>
#include <QMouseEvent>
#include <QScreen>
#include <QWSServer>

Calibration::Calibration()
{
    QRect desktop = QApplication::desktop()->geometry();
    desktop.moveTo(QPoint(0, 0));
    setGeometry(desktop);

    setFocusPolicy(Qt::StrongFocus);
    setFocus();
    setModal(true);

    int width = qt_screen->deviceWidth();
    int height = qt_screen->deviceHeight();

    int dlx = width/2;
    int dly = height/2;
    QLabel *label = new QLabel(this);
    label->setText("请点击十字叉校准触摸屏");
    QFont ft;
    ft.setPointSize(30);
    label->setFont(ft);
    QPalette pe;
    pe.setColor(QPalette::WindowText, Qt::white);
    label->setPalette(pe);
    label->adjustSize();

    label->size().width();

    label->move((width - label->size().width())/2, (height / 4));


    int dx = width / 10;
    int dy = height / 10;

    QPoint *points = data.screenPoints;
    points[QWSPointerCalibrationData::TopLeft] = QPoint(dx, dy);
    points[QWSPointerCalibrationData::BottomLeft] = QPoint(dx, height - dy);
    points[QWSPointerCalibrationData::BottomRight] = QPoint(width - dx, height - dy);
    points[QWSPointerCalibrationData::TopRight] = QPoint(width - dx, dy);
    points[QWSPointerCalibrationData::Center] = QPoint(width / 2, height / 2);

    pressCount = 0;
}

Calibration::~Calibration()
{
}

int Calibration::exec()
{
    QWSServer::mouseHandler()->clearCalibration();
    grabMouse();
    activateWindow();
    int ret = QDialog::exec();
    releaseMouse();
    return ret;
}

void Calibration::paintEvent(QPaintEvent*)
{//画十字+
    QPainter p(this);
    p.fillRect(rect(), Qt::black);

    QPoint point = data.screenPoints[pressCount];

    // Map to logical coordinates in case the screen is transformed
    QSize screenSize(qt_screen->deviceWidth(), qt_screen->deviceHeight());
    point = qt_screen->mapFromDevice(point, screenSize);

#if 0
    //十字  横线
    p.fillRect(point.x() - 6, point.y() - 1, 13, 3, Qt::red);
    //十字  竖线
    p.fillRect(point.x() - 1, point.y() - 6, 3, 13, Qt::red);
#else
    //设置pWigth 和 pPreWigth调节 十字叉大小 , pWigth 必须比 pPreWigth大
    //pPreWigth 十字外部直角边长度
    //pWigth （十字宽度-1)/2
    int pPreWigth = 5;
    int pWigth = 21;

    p.fillRect(point.x() - (pWigth-1), point.y() - (pWigth-1), pPreWigth, 1, Qt::white);
    p.fillRect(point.x() + (pWigth-pPreWigth) , point.y() - (pWigth-1), pPreWigth, 1, Qt::white);
    p.fillRect(point.x() - pWigth, point.y() - 1, pWigth*2+1, 3, Qt::white);
    p.fillRect(point.x() - (pWigth-1), point.y() + (pWigth-1), pPreWigth, 1, Qt::white);
    p.fillRect(point.x() + (pWigth-pPreWigth) , point.y() + (pWigth-1), pPreWigth, 1, Qt::white);

    p.fillRect(point.x() - (pWigth-1), point.y() - (pWigth-1), 1, pPreWigth, Qt::white);
    p.fillRect(point.x() - (pWigth-1), point.y() + (pWigth-pPreWigth), 1, pPreWigth, Qt::white);
    p.fillRect(point.x() - 1,  point.y() - pWigth, 3, pWigth*2+1, Qt::white);
    p.fillRect(point.x() + (pWigth-1), point.y() - (pWigth-1), 1, pPreWigth, Qt::white);
    p.fillRect(point.x() + (pWigth-1), point.y() + (pWigth-pPreWigth), 1, pPreWigth, Qt::white);
#endif

}

void Calibration::mouseReleaseEvent(QMouseEvent *event)
{
    // Map from device coordinates in case the screen is transformed
    QSize screenSize(qt_screen->width(), qt_screen->height());
    QPoint p = qt_screen->mapToDevice(event->pos(), screenSize);

    data.devPoints[pressCount] = p;

    if (++pressCount < 5)
        repaint();
    else
        accept();
}

void Calibration::accept()
{
    Q_ASSERT(pressCount == 5);
    QWSServer::mouseHandler()->calibrate(&data);
    QDialog::accept();
}
