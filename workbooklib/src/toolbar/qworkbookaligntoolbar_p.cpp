/*
    Copyright © Simon Meaden 2015.

    This file is part of the QWorkbook spreadsheet library.

    QWorkbook is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    QWorkbook is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with QWorkbook.  If not, see <http://www.gnu.org/licenses/>.

    It is also available on request from Simon Meaden info@smelecomp.co.uk.
*/
#include "qworkbookaligntoolbar_p.h"
#include "qworkbookaligntoolbar.h"
#include "qworkbookview.h"
#include "types.h"

QWorkbookAlignToolBarPrivate::QWorkbookAlignToolBarPrivate(QWorkbookAlignToolBar *q) :
    q_ptr(q) {

}

void QWorkbookAlignToolBarPrivate::init()  {

    pLeftBtn = new QPushButton(QIcon("://justify-left"), "", q_ptr);
    pLeftBtn->setToolTip("Align Left");
    pLeftBtn->setStyleSheet(ButtonStyle);
    pLeftBtn->setContentsMargins(0, 0, 0, 0);
    pLeftBtn->setCheckable(true);
    q_ptr->addWidget(pLeftBtn);
    q_ptr->connect(pLeftBtn, SIGNAL(clicked()), q_ptr, SLOT(alignHasClicked()));

    pHCentreBtn = new QPushButton(q_ptr);
    pHCentreBtn->setToolTip("Align Horizontal Centre");
    pHCentreBtn->setStyleSheet(ButtonStyle);
    pHCentreBtn->setContentsMargins(0, 0, 0, 0);
    pHCentreBtn->setCheckable(true);
    pHCentreBtn->setIcon(QIcon("://justify-centre"));
    q_ptr->addWidget(pHCentreBtn);
    q_ptr->connect(pHCentreBtn, SIGNAL(clicked()), q_ptr, SLOT(alignHasClicked()));

    pRightBtn = new QPushButton(q_ptr);
    pRightBtn->setToolTip("Align Right");
    pRightBtn->setStyleSheet(ButtonStyle);
    pRightBtn->setContentsMargins(0, 0, 0, 0);
    pRightBtn->setCheckable(true);
    pRightBtn->setIcon(QIcon("://justify-right"));
    q_ptr->addWidget(pRightBtn);
    q_ptr->connect(pRightBtn, SIGNAL(clicked()), q_ptr, SLOT(alignHasClicked()));

    pButtonGroup = new QButtonGroup(q_ptr);
    pButtonGroup->addButton(pLeftBtn);
    pButtonGroup->addButton(pHCentreBtn);
    pButtonGroup->addButton(pRightBtn);
    pLeftBtn->setChecked(true);

}

void QWorkbookAlignToolBarPrivate::setWorkbookView(QWorkbookView *view) {

    Q_Q(QWorkbookAlignToolBar);
    // view to bar
    q->connect(view, SIGNAL(selectionChanged(FormatStatus*)),
               q, SLOT(selectionChanged(FormatStatus*)));

    // bar to view (sets format in view)
    q->connect(q, SIGNAL(alignmentChanged(Qt::Alignment)),
               view, SLOT(setSelectionAlignment(Qt::Alignment)));

}

void QWorkbookAlignToolBarPrivate::selectionChanged(FormatStatus* status) {
    if (!status) return;

    // sets changes in buttons
    setAlign(status->bAllSameAlignment, status->mAlignment);
}

void QWorkbookAlignToolBarPrivate::alignHasClicked() {
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

    Q_Q(QWorkbookAlignToolBar);
    emit q->alignmentChanged(align);
}

void QWorkbookAlignToolBarPrivate::setAlign(bool set, Qt::Alignment alignment) {
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
