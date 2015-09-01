#include "workbookfunctiontoolbar.h"

WorkbookFunctionToolbar::WorkbookFunctionToolbar(QWidget *parent) : BaseToolbar(parent) {
    initBuild();
}

WorkbookFunctionToolbar::WorkbookFunctionToolbar(QString title, QWidget *parent) : BaseToolbar(title, parent) {
    initBuild();
}

void WorkbookFunctionToolbar::initBuild() {
    rangeEdit = new QLineEdit(this);
    rangeEdit->setReadOnly(true);
    addWidget(rangeEdit);

    manageNamesBtn = new QToolButton(this);
    manageNamesBtn->setCheckable(true);
    manageNamesBtn->setArrowType(Qt::DownArrow);
    addWidget(manageNamesBtn);

    funcWizardBtn = new QPushButton(this);
    funcWizardBtn->setToolTip(tr("Function Wizard"));
    funcWizardBtn->setIcon(QIcon("://fxwizard"));
    addWidget(funcWizardBtn);

    sumBtn = new QPushButton(this);
    sumBtn->setToolTip(tr("Sum"));
    sumBtn->setIcon(QIcon("://sum"));
    addWidget(sumBtn);

    funcBtn = new QPushButton(this);
    funcBtn->setToolTip(tr("Function"));
    funcBtn->setIcon(QIcon("://function"));
    addWidget(funcBtn);

    functionEdit = new QLineEdit(this);
    dropDownEdit = new QPlainTextEdit(this);
    dropDownEdit->setVisible(false);
    editor = functionEdit;
    addWidget(editor);

    dropBtn = new QToolButton(this);
    dropBtn->setCheckable(true);
    dropBtn->setArrowType(Qt::DownArrow);
    addWidget(dropBtn);
    connect(dropBtn, SIGNAL(clicked()), this, SLOT(drop()));

 }

void WorkbookFunctionToolbar::drop() {
    if (editor == functionEdit) {
        dropDownEdit->setVisible(true);
        functionEdit->setVisible(false);
        editor = dropDownEdit;
    } else {
        dropDownEdit->setVisible(false);
        functionEdit->setVisible(true);
        editor = functionEdit;
    }
}

void WorkbookFunctionToolbar::manageNames() {
    // TODO
}

void WorkbookFunctionToolbar::functionWizard() {
    // TODO
}

void WorkbookFunctionToolbar::sum() {
    // TODO
}

void WorkbookFunctionToolbar::function() {
    // TODO
}

void WorkbookFunctionToolbar::setRange(QString value){
    rangeEdit->setText(value);
}

