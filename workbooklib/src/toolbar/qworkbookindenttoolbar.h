#ifndef WORKBOOKINDENTTOOLBAR_H
#define WORKBOOKINDENTTOOLBAR_H

#include <QPushButton>

#include "workbook_global.h"
#include "basetoolbar.h"

class WORKBOOKSHARED_EXPORT WorkbookIndentToolbar : public BaseToolbar {
    Q_OBJECT
public:
    WorkbookIndentToolbar(QWidget *parent);
    WorkbookIndentToolbar(QString title, QWidget *parent);
    ~WorkbookIndentToolbar();

signals:

public slots:

protected slots:
    void indent();
    void undent();

protected:
    QPushButton *pIndentBtn, *pUndentBtn;
    void init();

};
#endif // WORKBOOKINDENTTOOLBAR_H
