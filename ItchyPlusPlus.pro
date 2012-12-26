#-------------------------------------------------
#
# Project created by QtCreator 2012-12-24T07:55:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ItchyPlusPlus
TEMPLATE = app


SOURCES += src/main.cpp\
        src/itchy.cpp

HEADERS  += src/itchy.h

FORMS    += itchy.ui

DESTDIR = build
OBJECTS_DIR = build/obj
MOC_DIR = build/moc
RCC_DIR = build/rcc
UI_DIR = build/ui

OTHER_FILES +=

RESOURCES += \
    itchy.qrc
