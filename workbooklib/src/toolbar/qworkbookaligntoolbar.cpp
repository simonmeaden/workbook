#include "qworkbookaligntoolbar.h"
#include "qworkbooktoolbar.h"

QWorkbookAlignToolbar::QWorkbookAlignToolbar(QWidget *parent) : BaseToolbar(parent) {
    init();
}

QWorkbookAlignToolbar::QWorkbookAlignToolbar(QString title, QWidget *parent) : BaseToolbar(title, parent) {
    init();
}

QWorkbookAlignToolbar::~QWorkbookAlignToolbar() {
}

void QWorkbookAlignToolbar::init()  {

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

    pButtonGroup = new QButtonGroup(this);
    pButtonGroup->addButton(pLeftBtn);
    pButtonGroup->addButton(pHCentreBtn);
    pButtonGroup->addButton(pRightBtn);
    pLeftBtn->setChecked(true);

}


void QWorkbookAlignToolbar::align() {
    Qt::Alignment valign = Qt::AlignVCenter;
    Qt::Alignment halign = Qt::AlignLeft;
    Qt::Alignment align;

    if (pLeftBtn->isChecked())
        halign = Qt::AlignLeft;
    else if (pHCentreBtn->isChecked())
        halign = Qt::AlignHCenter;
    else if (pRightBtn->isChecked())
        halign = Qt::AlignRight;

    align = halign | valign;

    emit alignmentChanged(align);
}

void QWorkbookAlignToolbar::setAlign(bool set, Qt::Alignment alignment) {
    if (set) {
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
    }
}
