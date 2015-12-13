QT          += core

TEMPLATE    = lib
CONFIG      += plugin shared

INCLUDEPATH  += $$PWD/../../include

DEFINES += WORKBOOK_LIBRARY

CONFIG(debug, debug|release) {
    $$qtLibraryTarget(lnfunction)
    DESTDIR = $$PWD/../../../../build/workbook/plugins
    OBJECTS_DIR = $$DESTDIR/.objd
    MOC_DIR = $$DESTDIR/.mocd
    RCC_DIR = $$DESTDIR/.qrcd
    UI_DIR = $$DESTDIR/.uid
}

CONFIG(release, debug|release) {
    $$qtLibraryTarget(lnfunction)
    DESTDIR = $$PWD/../../../../build/workbook/plugins
    OBJECTS_DIR = $$DESTDIR/.obj
    MOC_DIR = $$DESTDIR/.moc
    RCC_DIR = $$DESTDIR/.qrc
    UI_DIR = $$DESTDIR/.ui
}

HEADERS += \
    src/lnfunction.h

SOURCES += \
    src/lnfunction.cpp
