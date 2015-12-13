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
#include "qworkbookmergetoolbar_p.h"
#include "qworkbookmergetoolbar.h"
#include "qworkbookview.h"
#include "qworksheetview.h"
#include "types.h"

#include "workbook_global.h"

namespace QWorkbook {

QWorkbookMergeToolbarPrivate::QWorkbookMergeToolbarPrivate(QWorkbookMergeToolbar *q) :
    q_ptr(q),
    pView(NULL) {

}

void QWorkbookMergeToolbarPrivate::init() {

    pMergeBtn = new QPushButton(q_ptr);
    pMergeBtn->setToolTip(q_ptr->tr("Merge Cells"));
    pMergeBtn->setStyleSheet(ButtonStyle);
    pMergeBtn->setContentsMargins(0, 0, 0, 0);
    pMergeBtn->setIcon(QIcon("://cell-merge"));
    q_ptr->addWidget(pMergeBtn);
    q_ptr->connect(pMergeBtn, SIGNAL(clicked()), q_ptr, SLOT(merge()));

}

void QWorkbookMergeToolbarPrivate::setView(QObject *view) {

    Q_Q(QWorkbookMergeToolbar);
    QWorkbookView *wb;
    QWorksheetView *ws;

    // remove old connections
    if (pView) {
        wb = qobject_cast<QWorkbookView*>(pView);
        ws = qobject_cast<QWorksheetView*>(pView);

        if (wb) {
            q->disconnect(wb, SIGNAL(selectionChanged(FormatStatus*)),
                       q, SLOT(selectionChanged(FormatStatus*)));
            q->disconnect(q, SIGNAL(mergeChanged()),
                       wb, SLOT(setSelectionMerge()));
        } else if (ws) {
            q->disconnect(ws, SIGNAL(selectionChanged(FormatStatus*)),
                       q, SLOT(selectionChanged(FormatStatus*)));
            q->disconnect(q, SIGNAL(mergeChanged()),
                          ws, SLOT(setSelectionMerge()));
        }
    }

    // make new ones.
    wb = qobject_cast<QWorkbookView*>(view);
    ws = qobject_cast<QWorksheetView*>(view);
    if (wb) {
        q->connect(wb, SIGNAL(selectionChanged(FormatStatus*)),
                   q, SLOT(selectionChanged(FormatStatus*)));
        q->connect(q, SIGNAL(mergeChanged()),
                   wb, SLOT(setSelectionMerge()));
    } else if (ws) {
        q->connect(ws, SIGNAL(selectionChanged(FormatStatus*)),
                   q, SLOT(selectionChanged(FormatStatus*)));
        q->connect(q, SIGNAL(mergeChanged()),
                   ws, SLOT(setSelectionMerge()));
    }

    pView = view;

}

void QWorkbookMergeToolbarPrivate::selectionChanged(FormatStatus* status) {
    if (!status) return;

    // sets changes in buttons
    setMerge(status->bContiguous);
}


void QWorkbookMergeToolbarPrivate::merge() {

    Q_Q(QWorkbookMergeToolbar);
    emit q->mergeChanged();

}

void QWorkbookMergeToolbarPrivate::setMerge(bool enabled) {
    pMergeBtn->setEnabled(enabled);
}


}

