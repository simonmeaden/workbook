#include "qworkbookindenttoolbar.h"
#include "qworkbooktoolbar.h"

QWorkbookIndentToolbar::QWorkbookIndentToolbar(QWidget *parent) : BaseToolbar(parent) {
    init();
}

QWorkbookIndentToolbar::QWorkbookIndentToolbar(QString title, QWidget *parent) : BaseToolbar(title, parent) {
    init();
}

QWorkbookIndentToolbar::~QWorkbookIndentToolbar() {
}

void QWorkbookIndentToolbar::init()  {
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

void QWorkbookIndentToolbar::indent() {
    emit master->indentCells();
}

void QWorkbookIndentToolbar::undent() {
    emit master->undentCells();
}
