#include <QMessageBox>
#include <QFileDialog>
#include <qmenu.h>
#include <qaction.h>

#include <iostream>

#include "itchy.h"
#include "ui_itchy.h"
#include "mainpane.h"

itchy::itchy(QWidget *parent) : QMainWindow(parent), ui(new Ui::itchy) {
	ui->setupUi(this);

	ui->label_edit_menu->installEventFilter(this);
	ui->label_tips_menu->installEventFilter(this);
	ui->label_file_menu->installEventFilter(this);
    //Creates menu objects
    menuFile = new QMenu();
    menuEdit = new QMenu();

    //Creates button objects
    //FILE MENU
    btnNew = new QAction(tr("&New"), this);
    btnOpen = new QAction(tr("&Open"), this);
    btnSave = new QAction(tr("&Save"), this);

    //EDIT MENU


    //Adds buttons to menus
    menuFile->addAction(btnNew);
    menuFile->addAction(btnOpen);
    menuFile->addAction(btnSave);

    pane = new MainPane;

    ui->gridlayout_main_layout->removeItem(ui->verticalSpacer);
    ui->gridlayout_main_layout->addWidget(pane);

    //Connects Actions to their slots
    connect(btnOpen, SIGNAL(triggered()), SLOT(openFile()));
    connect(btnNew, SIGNAL(triggered()), SLOT(newFile()));
    connect(btnSave, SIGNAL(triggered()), SLOT(saveFile()));
}

itchy::~itchy() {
	delete ui;
}

void itchy::openFile() {
    projectFileName = QFileDialog::getOpenFileName(this);
    //Open logic here
}

void itchy::newFile() {
    //New file stuff here
}

void itchy::saveFile() {
    //Save file stuff here
}

bool itchy::eventFilter(QObject *obj, QEvent *event) {

    if(obj == ui->label_edit_menu || obj == ui->label_tips_menu || obj == ui->label_file_menu) {
		QLabel *label = qobject_cast<QLabel *>(obj);

		switch (event->type()) {
			case 2://mouse press
                if(label == ui->label_edit_menu) {
                    p.setX(label->geometry().bottomLeft().x() - 100);
                    p.setY(label->geometry().bottomLeft().y());
                    menuEdit->move(label->mapToGlobal(p));
                    menuEdit->show();
                }

                if(label == ui->label_tips_menu) {
                    QMessageBox::about(this, "Itchy++ Tips","About and Help goes here");
                }

                if(label == ui->label_file_menu){
                    p.setX(label->geometry().bottomLeft().x() - 60);
                    p.setY(label->geometry().bottomLeft().y());
                    menuFile->move(label->mapToGlobal(p));
                    menuFile->show();
                }
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
