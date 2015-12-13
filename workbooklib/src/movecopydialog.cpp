#include "movecopydialog.h"

#include "qworkbookview.h"

namespace QWorkbook {

MoveCopyDialog::MoveCopyDialog(QWorkbookView *parent) :
    QDialog(parent),
    pView(parent) {

    init();

}

MoveCopyDialog::MoveCopyDialog(QString name, QWorkbookView *parent) :
    QDialog(parent),
    pView(parent) {

    init();
    pNameEdit->setText(name);

}

void MoveCopyDialog::init() {
    QGridLayout *layout = new QGridLayout;
    setLayout(layout);

    pMoveBtn = new QRadioButton(tr("Move"), this);
    layout->addWidget(pMoveBtn, 0, 0);

    pCopyBtn = new QRadioButton(tr("Copy"), this);
    layout->addWidget(pCopyBtn, 0, 1);

    pGroup = new QButtonGroup(this);
    pGroup->addButton(pMoveBtn);
    pGroup->addButton(pCopyBtn);
    pMoveBtn->setChecked(true);

    QLabel *lbl1 = new QLabel(tr("Insert Before:"), this);
    layout->addWidget(lbl1, 1, 0, 1, 2);

    pListView = new QListWidget(this);
    pListView->setSelectionMode(QAbstractItemView::SingleSelection);
    pListView->addItems(pView->names());
    pListView->addItem(tr("-move to end position-"));
    QModelIndex index = pListView->rootIndex();
    pListView->setCurrentIndex(index);
    layout->addWidget(pListView, 2, 0, 1, 2);

    QLabel *lbl2 = new QLabel(tr("New &name"), this);
    layout->addWidget(lbl2, 3, 0, 1, 2);

    pNameEdit = new QLineEdit(this);
    layout->addWidget(pNameEdit, 4, 0, 1, 2);

    pOkBtn = new QPushButton(tr("OK"), this);
    layout->addWidget(pOkBtn, 5, 0);
    connect(pOkBtn, SIGNAL(clicked()), this, SLOT(accept()));

    pCancelBtn = new QPushButton(tr("Cancel"), this);
    layout->addWidget(pCancelBtn, 5, 1);
    connect(pCancelBtn, SIGNAL(clicked()), this, SLOT(reject()));
}

void MoveCopyDialog::setName(QString name) {
    pNameEdit->setText(name);
}

QString MoveCopyDialog::name() {
    return pNameEdit->text();
}

int MoveCopyDialog::tabIndex() {
    return pListView->currentRow();
}

MoveCopyDialog::Type MoveCopyDialog::type() {
    if (pMoveBtn->isChecked())
        return Move;
    else
        return Copy;
}

}
