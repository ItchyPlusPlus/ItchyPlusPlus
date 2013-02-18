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
    void openFile();
    void saveFile();
    void newFile();

private:
    Ui::itchy *ui;
    QMenu *menuFile;
    QMenu *menuEdit;
    QAction *btnNew;
    QAction *btnOpen;
    QAction *btnSave;
    QPoint p;
    QString projectFileName;
    MainPane *pane;

protected:
    bool eventFilter(QObject *obj, QEvent *event);
};

#endif // ITCHY_H
