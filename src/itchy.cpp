#include <QMessageBox>
#include <qmenu.h>
#include <qaction.h>

#include <iostream>

#include "itchy.h"
#include "ui_itchy.h"

itchy::itchy(QWidget *parent) : QMainWindow(parent), ui(new Ui::itchy) {
	ui->setupUi(this);

	ui->label_edit_menu->installEventFilter(this);
	ui->label_tips_menu->installEventFilter(this);
	ui->label_file_menu->installEventFilter(this);
    //declares the menu and the actions for adding
    menu = new QMenu();
    editTest = new QAction(tr("&Edit menu"), this);
    open = new QAction(tr("&Open"), this);
}

itchy::~itchy() {
	delete ui;
}

void itchy::label_edit_menu_hovered() {
    std::cout << "file!" << std::endl;
}

bool itchy::eventFilter(QObject *obj, QEvent *event) {

    if(obj == ui->label_edit_menu || obj == ui->label_tips_menu || obj == ui->label_file_menu) {
		QLabel *label = qobject_cast<QLabel *>(obj);

		switch (event->type()) {
			case 2://mouse press
                if(label == ui->label_edit_menu) {
                    menu->removeAction(open);
                    menu->addAction(editTest);
                }
                if(label == ui->label_tips_menu) {
                    QMessageBox::about(this, "Itchy++ Tips","About and Help goes here");
                    break;
                }
                if(label == ui->label_file_menu){
                    menu->removeAction(editTest);
                    menu->addAction(open);
                }
                menu->move(label->mapToGlobal(label->geometry().bottomLeft()));
				menu->show();
                break;
			case 10://mouse enter
				label->setStyleSheet("color:orange;");
				break;
			case 11://mouse leave
				label->setStyleSheet("color:white;");
				break;
			default:
				return false;
				break;
		}
	}
	//std::cout << "event " << event->type() << std::endl << std::flush;

	return false;
}
