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
#include "qworksheetview.h"
#include "types.h"

#include "workbook_global.h"

namespace QWorkbook {

AlignStatus AlignToolBarHelper::mStatus;

QWorkbookAlignToolBarPrivate::QWorkbookAlignToolBarPrivate(QWorkbookAlignToolBar *q) :
//    AlignToolBarHelper(),
    q_ptr(q),
    pView(NULL) {

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

void QWorkbookAlignToolBarPrivate::setView(QObject *view) {

    Q_Q(QWorkbookAlignToolBar);
    QWorkbookView *wb;
    QWorksheetView *ws;

    // remove old connections
    if (pView) {
        wb = qobject_cast<QWorkbookView*>(pView);
        ws = qobject_cast<QWorksheetView*>(pView);

        if (wb) {
            q->disconnect(wb, SIGNAL(selectionChanged(FormatStatus*)),
                       q, SLOT(selectionChanged(FormatStatus*)));
            q->disconnect(q, SIGNAL(alignmentChanged(Qt::Alignment)),
                       wb, SLOT(setSelectionAlignment(Qt::Alignment)));
        } else if (ws) {
            q->disconnect(ws, SIGNAL(selectionChanged(FormatStatus*)),
                       q, SLOT(selectionChanged(FormatStatus*)));
            q->disconnect(q, SIGNAL(alignmentChanged(Qt::Alignment)),
                       ws, SLOT(setSelectionAlignment(Qt::Alignment)));
        }
    }

    // make new ones.
    wb = qobject_cast<QWorkbookView*>(view);
    ws = qobject_cast<QWorksheetView*>(view);
    if (wb) {
        q->connect(wb, SIGNAL(selectionChanged(FormatStatus*)),
                   q, SLOT(selectionChanged(FormatStatus*)));
        q->connect(q, SIGNAL(alignmentChanged(Qt::Alignment)),
                   wb, SLOT(setSelectionAlignment(Qt::Alignment)));
    } else if (ws) {
        q->connect(ws, SIGNAL(selectionChanged(FormatStatus*)),
                   q, SLOT(selectionChanged(FormatStatus*)));
        q->connect(q, SIGNAL(alignmentChanged(Qt::Alignment)),
                   ws, SLOT(setSelectionAlignment(Qt::Alignment)));
    }

    pView = view;

}

void QWorkbookAlignToolBarPrivate::selectionChanged(FormatStatus* status) {
    if (!status) return;

    // sets changes in buttons
    setAlign(status->bAllSameAlignment, status->mAlignment);
}

void QWorkbookAlignToolBarPrivate::alignHasClicked() {

    if (pLeftBtn->isChecked())
        setHorizontalAlign(Qt::AlignLeft);
    else if (pHCentreBtn->isChecked())
        setHorizontalAlign(Qt::AlignHCenter);
    else if (pRightBtn->isChecked())
        setHorizontalAlign(Qt::AlignRight);

    Q_Q(QWorkbookAlignToolBar);
    emit q->alignmentChanged(alignment());
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

QWorkbookVerticalAlignToolBarPrivate::QWorkbookVerticalAlignToolBarPrivate(QWorkbookVerticalAlignToolBar *q) :
//    AlignToolBarHelper(),
    q_ptr(q),
    pView(NULL) {

}

void QWorkbookVerticalAlignToolBarPrivate::init()  {

    pTopBtn = new QPushButton(QIcon("://justify-top"), "", q_ptr);
    pTopBtn->setToolTip("Align top");
    pTopBtn->setStyleSheet(ButtonStyle);
    pTopBtn->setContentsMargins(0, 0, 0, 0);
    pTopBtn->setCheckable(true);
    q_ptr->addWidget(pTopBtn);
    q_ptr->connect(pTopBtn, SIGNAL(clicked()), q_ptr, SLOT(alignHasClicked()));

    pVCentreBtn = new QPushButton(q_ptr);
    pVCentreBtn->setToolTip("Align Vertical Centre");
    pVCentreBtn->setStyleSheet(ButtonStyle);
    pVCentreBtn->setContentsMargins(0, 0, 0, 0);
    pVCentreBtn->setCheckable(true);
    pVCentreBtn->setIcon(QIcon("://justify-middle"));
    q_ptr->addWidget(pVCentreBtn);
    q_ptr->connect(pVCentreBtn, SIGNAL(clicked()), q_ptr, SLOT(alignHasClicked()));

    pBottomBtn = new QPushButton(q_ptr);
    pBottomBtn->setToolTip("Align Bottom");
    pBottomBtn->setStyleSheet(ButtonStyle);
    pBottomBtn->setContentsMargins(0, 0, 0, 0);
    pBottomBtn->setCheckable(true);
    pBottomBtn->setIcon(QIcon("://justify-bottom"));
    q_ptr->addWidget(pBottomBtn);
    q_ptr->connect(pBottomBtn, SIGNAL(clicked()), q_ptr, SLOT(alignHasClicked()));

    pButtonGroup = new QButtonGroup(q_ptr);
    pButtonGroup->addButton(pTopBtn);
    pButtonGroup->addButton(pVCentreBtn);
    pButtonGroup->addButton(pBottomBtn);
    pTopBtn->setChecked(true);

}

void QWorkbookVerticalAlignToolBarPrivate::setView(QObject *view) {

    Q_Q(QWorkbookVerticalAlignToolBar);
    QWorkbookView *wb;
    QWorksheetView *ws;

    // remove old connections
    if (pView) {
        wb = qobject_cast<QWorkbookView*>(pView);
        ws = qobject_cast<QWorksheetView*>(pView);

        if (wb) {
            q->disconnect(wb, SIGNAL(selectionChanged(FormatStatus*)),
                       q, SLOT(selectionChanged(FormatStatus*)));
            q->disconnect(q, SIGNAL(alignmentChanged(Qt::Alignment)),
                       wb, SLOT(setSelectionAlignment(Qt::Alignment)));
        } else if (ws) {
            q->disconnect(ws, SIGNAL(selectionChanged(FormatStatus*)),
                       q, SLOT(selectionChanged(FormatStatus*)));
            q->disconnect(q, SIGNAL(alignmentChanged(Qt::Alignment)),
                       ws, SLOT(setSelectionAlignment(Qt::Alignment)));
        }
    }

    // make new ones.
    wb = qobject_cast<QWorkbookView*>(view);
    ws = qobject_cast<QWorksheetView*>(view);
    if (wb) {
        q->connect(wb, SIGNAL(selectionChanged(FormatStatus*)),
                   q, SLOT(selectionChanged(FormatStatus*)));
        q->connect(q, SIGNAL(alignmentChanged(Qt::Alignment)),
                   wb, SLOT(setSelectionAlignment(Qt::Alignment)));
    } else if (ws) {
        q->connect(ws, SIGNAL(selectionChanged(FormatStatus*)),
                   q, SLOT(selectionChanged(FormatStatus*)));
        q->connect(q, SIGNAL(alignmentChanged(Qt::Alignment)),
                   ws, SLOT(setSelectionAlignment(Qt::Alignment)));
    }

    pView = view;

}

void QWorkbookVerticalAlignToolBarPrivate::selectionChanged(FormatStatus* status) {
    if (!status) return;

    // sets changes in buttons
    setAlign(status->bAllSameAlignment, status->mAlignment);
}

void QWorkbookVerticalAlignToolBarPrivate::alignHasClicked() {

    if (pTopBtn->isChecked())
        setVerticalAlign(Qt::AlignTop);
    else if (pVCentreBtn->isChecked())
        setVerticalAlign(Qt::AlignVCenter);
    else if (pBottomBtn->isChecked())
        setVerticalAlign(Qt::AlignBottom);

    Q_Q(QWorkbookVerticalAlignToolBar);
    emit q->alignmentChanged(alignment());
}

void QWorkbookVerticalAlignToolBarPrivate::setAlign(bool set, Qt::Alignment alignment) {
    if (set) {
        if (alignment.testFlag(Qt::AlignTop))
            pTopBtn->setChecked(true);
        else
            pTopBtn->setChecked(false);

        if (alignment.testFlag(Qt::AlignVCenter))
            pVCentreBtn->setChecked(true);
        else
            pVCentreBtn->setChecked(false);

        if (alignment.testFlag(Qt::AlignBottom))
            pBottomBtn->setChecked(true);
        else
            pBottomBtn->setChecked(false);
    }
}

}

