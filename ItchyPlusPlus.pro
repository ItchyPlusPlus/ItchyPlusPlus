QT       += core gui

QMAKE_CXXFLAGS += -fprofile-arcs -ftest-coverage
QMAKE_LDFLAGS += -fprofile-arcs -ftest-coverage
LIBS += -lgcov

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ItchyPlusPlus
TEMPLATE = app


SOURCES += src/itchy.cpp\
            src/guiobjects.cpp\
            src/main.cpp \
            src/mainpane.cpp \
    src/blockwidget.cpp \
    src/scriptpane.cpp

HEADERS  += src/itchy.h\
            src/guiobjects.h \
            src/mainpane.h \
    src/blockwidget.h \
    src/scriptpane.h

FORMS    += itchy.ui

DESTDIR = build
OBJECTS_DIR = build/obj
MOC_DIR = build/moc
RCC_DIR = build/rcc
UI_DIR = build/ui

OTHER_FILES +=

RESOURCES += \
    itchy.qrc
