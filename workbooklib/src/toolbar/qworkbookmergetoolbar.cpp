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
#include "qworkbookmergetoolbar.h"
#include "qworkbookmergetoolbar_p.h"
#include "qworkbookview.h"
#include "qworksheetview.h"

#include "workbook_global.h"

namespace QWorkbook {

QWorkbookMergeToolbar::QWorkbookMergeToolbar(QWidget *parent) :
    QToolBar(parent),
    d_ptr(new QWorkbookMergeToolbarPrivate(this)){
    /* Have to do it here because d_ptr is not yet created
     * when th private class constructor is called */
    d_ptr->init();

}

QWorkbookMergeToolbar::QWorkbookMergeToolbar(QString title,QWidget *parent) :
    QToolBar(title, parent),
    d_ptr(new QWorkbookMergeToolbarPrivate(this)){

    /* Have to do it here because d_ptr is not yet created
     * when th private class constructor is called */
    d_ptr->init();

}

void QWorkbookMergeToolbar::setWorkbookView(QWorkbookView *view) {

    Q_D(QWorkbookMergeToolbar);
    d->setView(view);

}

void QWorkbookMergeToolbar::setWorksheetView(QWorksheetView *view) {

    Q_D(QWorkbookMergeToolbar);
    d->setView(view);

}

void QWorkbookMergeToolbar::selectionChanged(FormatStatus* status) {

    Q_D(QWorkbookMergeToolbar);
    d->selectionChanged(status);

}

void QWorkbookMergeToolbar::merge() {

    Q_D(QWorkbookMergeToolbar);
    d->merge();

}

void QWorkbookMergeToolbar::setMerge(bool merge) {

    Q_D(QWorkbookMergeToolbar);
    d->setMerge(merge);

}


}

