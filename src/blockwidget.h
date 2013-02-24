#ifndef BLOCKWIDGET_H
#define BLOCKWIDGET_H

#include <QWidget>

class BlockWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BlockWidget(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    
signals:
    
public slots:
    
};

#endif // BLOCKWIDGET_H
