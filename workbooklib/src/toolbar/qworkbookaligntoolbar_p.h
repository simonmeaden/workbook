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
#ifndef QWORKBOOKALIGNTOOLBARPRIVATE_H
#define QWORKBOOKALIGNTOOLBARPRIVATE_H

#include <QPushButton>
#include <QButtonGroup>


class QWorkbookAlignToolBar;
class QWorkbookView;
class FormatStatus;

class QWorkbookAlignToolBarPrivate {
    Q_DECLARE_PUBLIC(QWorkbookAlignToolBar)
public:
    QWorkbookAlignToolBarPrivate(QWorkbookAlignToolBar *q);
    virtual ~QWorkbookAlignToolBarPrivate() {}

    void setAlign(bool, Qt::Alignment);
    void setWorkbookView(QWorkbookView *);
    void selectionChanged(FormatStatus*);

protected:
    QPushButton *pLeftBtn, *pHCentreBtn, *pRightBtn;
    QButtonGroup *pButtonGroup;
    QWorkbookAlignToolBar *q_ptr;

    void init();
    void alignHasClicked();

};

#endif // QWORKBOOKALIGNTOOLBARPRIVATE_H
