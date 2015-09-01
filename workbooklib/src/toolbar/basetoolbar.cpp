#include "basetoolbar.h"

#include "qworkbooktoolbar.h"

const QString BaseToolbar::buttonStyle = "padding: 0px; " \
                                         "margin: 0px; " \
        ;


BaseToolbar::BaseToolbar(QWidget *parent) :
    QToolBar(parent),
    master(static_cast<QWorkbookToolBar*>(parent)) {

    Q_INIT_RESOURCE(workbook);

}

BaseToolbar::BaseToolbar(QString title, QWidget *parent) :
    QToolBar(title, parent),
    master(static_cast<QWorkbookToolBar*>(parent)) {

}
