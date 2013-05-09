#include <QtGui>
#include "blockwidget.h"


    QPainterPath *path;
BlockWidget::BlockWidget(QWidget *parent) :
    QWidget(parent) {
    int width = 100;

    path = new QPainterPath();
    path->moveTo(0, CORNER_INSET);
    path->lineTo(CORNER_INSET, 0);
    path->lineTo(NotchL1, 0);
    path->lineTo(NotchL2, NotchDepth);
    path->lineTo(NotchR1, NotchDepth);
    path->lineTo(NotchR2, 0);
    path->lineTo((width - CORNER_INSET), 0);
    path->lineTo(width, CORNER_INSET);

    int TOPH = 20;

    path->lineTo(width, TOPH - CORNER_INSET);
    path->lineTo(width - CORNER_INSET, TOPH);

    path->lineTo(0 + NotchR2, TOPH);
    path->lineTo(0 + NotchR1, TOPH + NotchDepth);
    path->lineTo(0 + NotchL2, TOPH + NotchDepth);
    path->lineTo(0 + NotchL1, TOPH);

    path->lineTo(0 + CORNER_INSET, TOPH);
    path->lineTo(0, TOPH-CORNER_INSET);

    path->lineTo(0, CORNER_INSET);

}

void BlockWidget::paintEvent(QPaintEvent *) {
    QPainter painter(this);

    painter.setPen(QPen(QColor(0, 0, 0, 153), 1));
    painter.setBrush(QColor(122, 163, 39));
    painter.drawPath(*path);

    painter.drawText(10, 10, "BlockWidget");
}

bool _mouseDown = 0;

void BlockWidget::mousePressEvent(QMouseEvent *event) {
  _mouseDown = true;
}
void BlockWidget::mouseReleaseEvent(QMouseEvent *event) {
  _mouseDown = false;
}
void BlockWidget::mouseMoveEvent(QMouseEvent *event) {
  if(_mouseDown) {
      move(mapToParent(event->pos()));
    }
}
