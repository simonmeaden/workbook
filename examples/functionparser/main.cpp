#include "mainwindow.h"
#include <QApplication>

QWORKBOOK_USE_NAMESPACE

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
