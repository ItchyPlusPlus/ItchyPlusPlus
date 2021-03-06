#include <QtGui>
#include <QImage>
#include <QRgb>
#include <stdlib.h>
#include "mainpane.h"
#include "blockwidget.h"

BlockWidget *bw;

MainPane::MainPane(QWidget *parent) :
    QWidget(parent) {
    //setFixedSize(200, 200);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //bw.setParent(parent);
    bw=new BlockWidget(this);
    bw->move(500, 500);
    bw->show();
}

void MainPane::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    QImage image(480, 360, QImage::Format_RGB32);
    for(int x = 0; x < 480; x++) {
        for(int y = 0; y < 360; y++) {
            int r = rand() % (255 - 0 + 1) + 0;
            int g = rand() % (255 - 0 + 1) + 0;
            int b = rand() % (255 - 0 + 1) + 0;
            image.setPixel(x, y, qRgb(r, g, b));
        }
    }
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawImage(0, 0, image);
    //bw->move(mapFromGlobal(QCursor::pos()));
    update();
}
