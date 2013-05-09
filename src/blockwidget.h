#ifndef BLOCKWIDGET_H
#define BLOCKWIDGET_H

#include <QWidget>

const int CORNER_INSET = 3;
const int NotchL1 = 13;
const int NotchL2 = 16;
const int NotchR1 = 24;
const int NotchR2 = 27;
const int NotchDepth = 3;

class BlockWidget : public QWidget
{
    Q_OBJECT
public:

    explicit BlockWidget(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);

    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
protected:

signals:
    
public slots:

};

#endif // BLOCKWIDGET_H
