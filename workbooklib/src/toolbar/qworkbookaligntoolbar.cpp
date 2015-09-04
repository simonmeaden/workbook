#include "workbookaligntoolbar.h"
#include "qworkbooktoolbar.h"

WorkbookAlignToolbar::WorkbookAlignToolbar(QWidget *parent) : BaseToolbar(parent) {
    init();
}

WorkbookAlignToolbar::WorkbookAlignToolbar(QString title, QWidget *parent) : BaseToolbar(title, parent) {
    init();
}

WorkbookAlignToolbar::~WorkbookAlignToolbar() {
}

void WorkbookAlignToolbar::init()  {

    pLeftBtn = new QPushButton(QIcon("://justify-left"), "", this);
    pLeftBtn->setToolTip("Align Left");
    pLeftBtn->setStyleSheet(buttonStyle);
    pLeftBtn->setContentsMargins(0, 0, 0, 0);
    pLeftBtn->setCheckable(true);
    addWidget(pLeftBtn);
    connect(pLeftBtn, SIGNAL(clicked()), this, SLOT(align()));

    pHCentreBtn = new QPushButton(this);
    pHCentreBtn->setToolTip("Align Horizontal Centre");
    pHCentreBtn->setStyleSheet(buttonStyle);
    pHCentreBtn->setContentsMargins(0, 0, 0, 0);
    pHCentreBtn->setCheckable(true);
    pHCentreBtn->setIcon(QIcon("://justify-centre"));
    addWidget(pHCentreBtn);
    connect(pHCentreBtn, SIGNAL(clicked()), this, SLOT(align()));

    pRightBtn = new QPushButton(this);
    pRightBtn->setToolTip("Align Right");
    pRightBtn->setStyleSheet(buttonStyle);
    pRightBtn->setContentsMargins(0, 0, 0, 0);
    pRightBtn->setCheckable(true);
    pRightBtn->setIcon(QIcon("://justify-right"));
    addWidget(pRightBtn);
    connect(pRightBtn, SIGNAL(clicked()), this, SLOT(align()));

    pFillBtn = new QPushButton(this);
    pFillBtn->setToolTip("Justify");
    pFillBtn->setStyleSheet(buttonStyle);
    pFillBtn->setContentsMargins(0, 0, 0, 0);
    pFillBtn->setCheckable(true);
    pFillBtn->setIcon(QIcon("://justify-fill"));
    addWidget(pFillBtn);
    connect(pFillBtn, SIGNAL(clicked()), this, SLOT(align()));

    pMergeBtn = new QPushButton(this);
    pMergeBtn->setToolTip("Merge Cells");
    pMergeBtn->setStyleSheet(buttonStyle);
    pMergeBtn->setContentsMargins(0, 0, 0, 0);
    pMergeBtn->setCheckable(true);
    pMergeBtn->setIcon(QIcon("://cell-merge"));
    addWidget(pMergeBtn);
    connect(pMergeBtn, SIGNAL(clicked()), this, SLOT(merge()));

    pButtonGroup = new QButtonGroup(this);
    pButtonGroup->addButton(pLeftBtn);
    pButtonGroup->addButton(pHCentreBtn);
    pButtonGroup->addButton(pRightBtn);
    pButtonGroup->addButton(pFillBtn);
    pLeftBtn->setChecked(true);
}

void WorkbookAlignToolbar::merge() {
    emit master->mergeCells();
}

void WorkbookAlignToolbar::align() {
    Qt::Alignment valign = Qt::AlignVCenter;
    Qt::Alignment halign = Qt::AlignLeft;
    Qt::Alignment align;

    if (pLeftBtn->isChecked())
        halign = Qt::AlignLeft;
    else if (pHCentreBtn->isChecked())
        halign = Qt::AlignHCenter;
    else if (pRightBtn->isChecked())
        halign = Qt::AlignRight;
    else if (pFillBtn->isChecked())
        halign = Qt::AlignJustify;

    align = halign | valign;

    emit master->alignmentChanged(align);
}

void WorkbookAlignToolbar::setAlign(Qt::Alignment alignment) {
    if (alignment.testFlag(Qt::AlignLeft))
        pLeftBtn->setChecked(true);
    else
        pLeftBtn->setChecked(false);

    if (alignment.testFlag(Qt::AlignCenter))
        pHCentreBtn->setChecked(true);
    else
        pHCentreBtn->setChecked(false);

    if (alignment.testFlag(Qt::AlignRight))
        pRightBtn->setChecked(true);
    else
        pRightBtn->setChecked(false);

    if (alignment.testFlag(Qt::AlignJustify))
        pFillBtn->setChecked(true);
    else
        pFillBtn->setChecked(false);
}
