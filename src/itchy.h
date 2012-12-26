#ifndef ITCHY_H
#define ITCHY_H

#include <QMainWindow>

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
    void on_actionScratch_Project_triggered();

    void on_actionItchy_Project_triggered();

    void on_actionHelp_triggered();

    void on_actionAbout_triggered();

private:
    Ui::itchy *ui;
};

#endif // ITCHY_H
