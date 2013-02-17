#ifndef ITCHY_H
#define ITCHY_H

#include <QMainWindow>
#include "mainpane.h"

namespace Ui {
class itchy;
}

class itchy : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit itchy(QWidget *parent = 0);
    ~itchy();
    
private slots:

    void label_edit_menu_hovered();

private:
    Ui::itchy *ui;
    QMenu *menu;
    QAction *editTest;
    QAction *tipTest;
    QAction *open;
    QPoint p;
    MainPane *pane;

protected:
    bool eventFilter(QObject *obj, QEvent *event);
};

#endif // ITCHY_H
