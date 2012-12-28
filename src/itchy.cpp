#include <QMessageBox>

#include <iostream>

#include "itchy.h"
#include "ui_itchy.h"

itchy::itchy(QWidget *parent) :
		QMainWindow(parent), ui(new Ui::itchy) {
	ui->setupUi(this);

	ui->label_edit_menu->installEventFilter(this);
	ui->label_tips_menu->installEventFilter(this);
	ui->label_file_menu->installEventFilter(this);
}

itchy::~itchy() {
	delete ui;
}

void itchy::on_actionScratch_Project_triggered() {
	QMessageBox::information(NULL, "Itchy++ | Open Scratch Project",
			"Feature not implemented yet!");
}

void itchy::on_actionItchy_Project_triggered() {
	QMessageBox::information(NULL, "Itchy++ | Open Itchy Project",
			"Feature not implemented yet!");
}

void itchy::on_actionHelp_triggered() {
	QMessageBox::information(NULL, "Itchy++ | Help",
			"Feature not implemented yet!");
}

void itchy::on_actionAbout_triggered() {
	QMessageBox::about(NULL, "Itchy++ | About", "Insert about here");
}

void itchy::on_actionOpen_triggered() {
	QMessageBox::information(NULL, "Itchy++ | Open",
			"Feature not implemented yet!");
}

void itchy::label_edit_menu_hovered() {
std::cout << "file!";
}

bool itchy::eventFilter(QObject *obj, QEvent *event){

	if(obj == ui->label_edit_menu || obj == ui->label_tips_menu || obj == ui->label_file_menu){
		QLabel *label = qobject_cast<QLabel *>(obj);
		switch (event->type()) {
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
