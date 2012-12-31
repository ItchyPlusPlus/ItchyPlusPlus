#include "itchy.h"
#include "guiobjects.h"
#include <QApplication>
#include <qsplashscreen.h>
#include <iostream>


int main(int argc, char *argv[]) {
	std::cout << "Itchy++" << std::flush;

	QApplication a(argc, argv);

	SplashScreen *splash = new SplashScreen(true, QPixmap(":/logos/res/splash.png"));
	splash->show();

	itchy w;
    w.show();

    splash->hide();

	return a.exec();
}
