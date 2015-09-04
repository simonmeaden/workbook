#include "qworkbookmergetoolbar.h"

QWorkbookMergeToolbar::QWorkbookMergeToolbar(QWidget *parent) : BaseToolbar(parent) {
    init();
}

QWorkbookMergeToolbar::QWorkbookMergeToolbar(QString title,QWidget *parent) : BaseToolbar(title, parent) {
    init();
}

QWorkbookMergeToolbar::~QWorkbookMergeToolbar() {

}

void QWorkbookMergeToolbar::init() {

    pMergeBtn = new QPushButton(this);
    pMergeBtn->setToolTip("Merge Cells");
    pMergeBtn->setStyleSheet(buttonStyle);
    pMergeBtn->setContentsMargins(0, 0, 0, 0);
    pMergeBtn->setCheckable(true);
    pMergeBtn->setIcon(QIcon("://cell-merge"));
    addWidget(pMergeBtn);
    connect(pMergeBtn, SIGNAL(clicked()), this, SLOT(merge()));

}

void QWorkbookMergeToolbar::merge() {
    emit mergeSelection(pMergeBtn->isChecked());
}

void QWorkbookMergeToolbar::setMerge(bool merge) {
    pMergeBtn->setChecked(merge);
}

