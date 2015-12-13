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
#ifndef QWORKBOOKINDENTTOOLBARPRIVATE_H
#define QWORKBOOKINDENTTOOLBARPRIVATE_H

#include <QPushButton>


#include "workbook_global.h"

namespace QWorkbook {

class QWorkbookIndentToolBar;
class QWorkbookView;
class FormatStatus;

class QWorkbookIndentToolBarPrivate {
    Q_DECLARE_PUBLIC(QWorkbookIndentToolBar)
public:
    QWorkbookIndentToolBarPrivate(QWorkbookIndentToolBar *q);
    virtual ~QWorkbookIndentToolBarPrivate() {}

    void indent();
    void undent();

protected:
    QPushButton *pIndentBtn, *pUndentBtn;
    QWorkbookIndentToolBar *q_ptr;
    void *pView;

    void init();

};


}

#endif // QWORKBOOKINDENTTOOLBARPRIVATE_H
