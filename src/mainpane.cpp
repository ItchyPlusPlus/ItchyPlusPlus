#include <QtGui>
#include <QImage>
#include <QRgb>
#include <stdlib.h>
#include "mainpane.h"

MainPane::MainPane(QWidget *parent) :
    QWidget(parent) {
    //setFixedSize(200, 200);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void MainPane::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    QImage image(640, 480, QImage::Format_RGB32);
    for(int x = 0; x < 640; x++) {
        for(int y = 0; y < 480; y++) {
            int r = rand() % (255 - 0 + 1) + 0;
            int g = rand() % (255 - 0 + 1) + 0;
            int b = rand() % (255 - 0 + 1) + 0;
            image.setPixel(x, y, qRgb(r, g, b));
        }
    }
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawImage(0, 0, image);
    update();
}
