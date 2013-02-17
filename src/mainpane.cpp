#include <QtGui>
#include "mainpane.h"

MainPane::MainPane(QWidget *parent) :
    QWidget(parent) {
    //setFixedSize(200, 200);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void MainPane::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawText(20, 20, QString("Hello World! Itchy++"));
    painter.drawRoundRect(40, 40, 50, 50);
}
