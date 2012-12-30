
#ifndef GUIOBJECTS_H_
#define GUIOBJECTS_H_

#include <qsplashscreen.h>
#include <iostream>


class SplashScreen : public QSplashScreen{
	bool unclickable;

public:

	SplashScreen(bool punclickable, QPixmap image) : QSplashScreen() {
		unclickable = punclickable;

		setPixmap(image);
	}

	void mousePressEvent(QMouseEvent *event){

	}

};

#endif /* GUIOBJECTS_H_ */
