#include <QtGui>
#include "blockwidget.h"

BlockWidget::BlockWidget(QWidget *parent) :
    QWidget(parent) {
}

void BlockWidget::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.drawText(20, 20, "BlockWidget");
}
