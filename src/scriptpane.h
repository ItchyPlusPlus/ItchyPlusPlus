#ifndef SCRIPTPANE_H
#define SCRIPTPANE_H

#include <QWidget>

class scriptpane : public QWidget
{
  Q_OBJECT
public:
  explicit scriptpane(QWidget *parent = 0);
  void paintEvent(QPaintEvent *);

signals:
  
public slots:
  
};

#endif // SCRIPTPANE_H
