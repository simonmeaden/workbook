#include "qworkbookfunctiontoolbar.h"

QWorkbookFunctionToolbar::QWorkbookFunctionToolbar(QWidget *parent) : BaseToolbar(parent) {
    initBuild();
}

QWorkbookFunctionToolbar::QWorkbookFunctionToolbar(QString title, QWidget *parent) : BaseToolbar(title, parent) {
    initBuild();
}

void QWorkbookFunctionToolbar::initBuild() {
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

void QWorkbookFunctionToolbar::drop() {
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

void QWorkbookFunctionToolbar::manageNames() {
    // TODO
}

void QWorkbookFunctionToolbar::functionWizard() {
    // TODO
}

void QWorkbookFunctionToolbar::sum() {
    // TODO
}

void QWorkbookFunctionToolbar::function() {
    // TODO
}

void QWorkbookFunctionToolbar::setRange(QString value){
    rangeEdit->setText(value);
}

