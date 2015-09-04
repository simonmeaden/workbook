#include "workbookindenttoolbar.h"
#include "qworkbooktoolbar.h"

WorkbookIndentToolbar::WorkbookIndentToolbar(QWidget *parent) : BaseToolbar(parent) {
    init();
}

WorkbookIndentToolbar::WorkbookIndentToolbar(QString title, QWidget *parent) : BaseToolbar(title, parent) {
    init();
}

WorkbookIndentToolbar::~WorkbookIndentToolbar() {
}

void WorkbookIndentToolbar::init()  {
    pUndentBtn = new QPushButton(this);
    pUndentBtn->setToolTip("Decrease Indent");
    pUndentBtn->setStyleSheet(buttonStyle);
    pUndentBtn->setContentsMargins(0, 0, 0, 0);
    pUndentBtn->setIcon(QIcon("://undent"));
    addWidget(pUndentBtn);
    connect(pUndentBtn, SIGNAL(clicked()), this, SLOT(undent()));

    pIndentBtn = new QPushButton(QIcon("://indent"), "", this);
    pIndentBtn->setToolTip("Increase Indent");
    pIndentBtn->setStyleSheet(buttonStyle);
    pIndentBtn->setContentsMargins(0, 0, 0, 0);
    addWidget(pIndentBtn);
    connect(pIndentBtn, SIGNAL(clicked()), this, SLOT(indent()));

}

void WorkbookIndentToolbar::indent() {
    emit master->indentCells();
}

void WorkbookIndentToolbar::undent() {
    emit master->undentCells();
}
