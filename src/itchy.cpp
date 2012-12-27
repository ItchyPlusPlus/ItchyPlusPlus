#include <QMessageBox>

#include "itchy.h"
#include "ui_itchy.h"

itchy::itchy(QWidget *parent) :
		QMainWindow(parent), ui(new Ui::itchy) {
	ui->setupUi(this);
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
