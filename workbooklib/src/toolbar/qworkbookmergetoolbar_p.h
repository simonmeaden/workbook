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
#ifndef QWORKBOOKMERGETOOLBARPRIVATE_H
#define QWORKBOOKMERGETOOLBARPRIVATE_H

#include <QPushButton>

#include "workbook_global.h"

namespace QWorkbook {

class QWorkbookMergeToolbar;
class QWorkbookView;
class FormatStatus;

class QWorkbookMergeToolbarPrivate {
    Q_DECLARE_PUBLIC(QWorkbookMergeToolbar)
public:
    QWorkbookMergeToolbarPrivate(QWorkbookMergeToolbar *q);
    virtual ~QWorkbookMergeToolbarPrivate() {}

    void setMerge(bool);
    void merge();
    void setView(QObject *);
    void selectionChanged(FormatStatus*);

protected:
    QPushButton *pMergeBtn;
    QWorkbookMergeToolbar *q_ptr;
    QObject *pView;

    void init();

};


}

#endif // QWORKBOOKMERGETOOLBARPRIVATE_H
