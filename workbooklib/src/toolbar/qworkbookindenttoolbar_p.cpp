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
#include "qworkbookindenttoolbar_p.h"
#include "qworkbookindenttoolbar.h"
#include "qworkbookview.h"
#include "types.h"

QWorkbookIndentToolBarPrivate::QWorkbookIndentToolBarPrivate(QWorkbookIndentToolBar *q) :
    q_ptr(q) {

}

void QWorkbookIndentToolBarPrivate::init()  {
    Q_Q(QWorkbookIndentToolBar);

    pUndentBtn = new QPushButton(q);
    pUndentBtn->setToolTip("Decrease Indent");
    pUndentBtn->setStyleSheet(ButtonStyle);
    pUndentBtn->setContentsMargins(0, 0, 0, 0);
    pUndentBtn->setIcon(QIcon("://undent"));
    q->addWidget(pUndentBtn);
    q->connect(pUndentBtn, SIGNAL(clicked()), q, SLOT(undent()));

    pIndentBtn = new QPushButton(QIcon("://indent"), "", q);
    pIndentBtn->setToolTip("Increase Indent");
    pIndentBtn->setStyleSheet(ButtonStyle);
    pIndentBtn->setContentsMargins(0, 0, 0, 0);
    q->addWidget(pIndentBtn);
    q->connect(pIndentBtn, SIGNAL(clicked()), q, SLOT(indent()));

}

void QWorkbookIndentToolBarPrivate::indent() {
    Q_Q(QWorkbookIndentToolBar);
    emit q->indentCells();
}

void QWorkbookIndentToolBarPrivate::undent() {
    Q_Q(QWorkbookIndentToolBar);
    emit q->undentCells();
}
