#ifndef WORKBOOKFUNCTIONTOOLBAR_H
#define WORKBOOKFUNCTIONTOOLBAR_H

#include <QPlainTextEdit>
#include <QPushButton>
#include <QToolButton>
#include <QLineEdit>

#include "workbook_global.h"
#include "basetoolbar.h"

class WORKBOOKSHARED_EXPORT WorkbookFunctionToolbar : public BaseToolbar {
    Q_OBJECT
public:
    WorkbookFunctionToolbar(QWidget *parent);
    WorkbookFunctionToolbar(QString title, QWidget *parent);

signals:

public slots:
    void setRange(QString value);

protected slots:
    void drop();
    void manageNames();
    void functionWizard();
    void sum();
    void function();

protected:
    QLineEdit *rangeEdit, *functionEdit;
    QPlainTextEdit *dropDownEdit;
    QToolButton *manageNamesBtn, *dropBtn;
    QPushButton *funcWizardBtn, *sumBtn, *funcBtn;
    QWidget *editor;

    void initBuild();

};
#endif // WORKBOOKFUNCTIONTOOLBAR_H
