#ifndef MAINPANE_H
#define MAINPANE_H

#include <QWidget>

class MainPane : public QWidget
{
    Q_OBJECT
public:
    explicit MainPane(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *event);
    
signals:
    
public slots:
    
};

#endif // MAINPANE_H
