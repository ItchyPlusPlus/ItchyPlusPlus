QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ItchyPlusPlus
TEMPLATE = app


SOURCES += src/*.cpp\

HEADERS  += src/*.h

FORMS    += itchy.ui

DESTDIR = build
OBJECTS_DIR = build/obj
MOC_DIR = build/moc
RCC_DIR = build/rcc
UI_DIR = build/ui

OTHER_FILES +=

RESOURCES += \
    itchy.qrc
