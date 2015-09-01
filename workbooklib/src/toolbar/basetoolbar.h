#ifndef BASETOOLBAR_H
#define BASETOOLBAR_H

#include <QToolBar>

#include <widgets/fontcombobox.h>

#include "workbook_global.h"


class QWorkbookToolBar;

class WORKBOOKSHARED_EXPORT BaseToolbar : public QToolBar {
    Q_OBJECT
public:
    BaseToolbar(QWidget *parent);
    BaseToolbar(QString title, QWidget *parent);

protected:
    QWorkbookToolBar *master;
    const static QString buttonStyle;

};

#endif // BASETOOLBAR_H
