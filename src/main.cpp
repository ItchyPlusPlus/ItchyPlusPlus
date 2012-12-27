#include "itchy.h"
#include <QApplication>
#include <iostream>

int main(int argc, char *argv[]) {
	std::cout << "Itchy++" << std::flush;

	QApplication a(argc, argv);
	itchy w;
	w.show();

	return a.exec();
}
