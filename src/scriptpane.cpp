#include <QtGui>
#include "scriptpane.h"

scriptpane::scriptpane(QWidget *parent) :
  QWidget(parent)
{
}
void scriptpane::paintEvent(QPaintEvent *) {
  QPainter painter(this);
}
