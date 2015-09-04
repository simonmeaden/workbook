#ifndef WORKBOOKINDENTTOOLBAR_H
#define WORKBOOKINDENTTOOLBAR_H

#include <QPushButton>

#include "workbook_global.h"
#include "basetoolbar.h"

class WORKBOOKSHARED_EXPORT QWorkbookIndentToolbar : public BaseToolbar {
    Q_OBJECT
public:
    QWorkbookIndentToolbar(QWidget *parent);
    QWorkbookIndentToolbar(QString title, QWidget *parent);
    ~QWorkbookIndentToolbar();

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
