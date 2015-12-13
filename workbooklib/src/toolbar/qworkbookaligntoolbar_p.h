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

#include "workbook_global.h"

namespace QWorkbook {

class QWorkbookAlignToolBar;
class QWorkbookView;
class FormatStatus;
class QWorkbookAlignToolBar;
class QWorkbookVerticalAlignToolBar;

struct AlignStatus {

    AlignStatus() {
        mVAalign = Qt::AlignVCenter;
        mHAlign = Qt::AlignLeft;
        mAlign = mVAalign | mHAlign;
    }
    virtual ~AlignStatus() {}


    Qt::Alignment mVAalign;
    Qt::Alignment mHAlign;
    Qt::Alignment mAlign;

};

class AlignToolBarHelper {
public:
    AlignToolBarHelper() {    }
    virtual ~AlignToolBarHelper() {}

    void setVerticalAlign(Qt::Alignment align) {

        mStatus.mVAalign = align;

        mStatus.mAlign = mStatus.mHAlign | mStatus.mVAalign;

    }

    void setHorizontalAlign(Qt::Alignment align) {

        mStatus.mHAlign = align;

        mStatus.mAlign = mStatus.mHAlign | mStatus.mVAalign;

    }

    Qt::Alignment alignment() { return mStatus.mAlign; }

protected:
    static AlignStatus mStatus;

};


class QWorkbookAlignToolBarPrivate : public AlignToolBarHelper {
    Q_DECLARE_PUBLIC(QWorkbookAlignToolBar)
public:
    QWorkbookAlignToolBarPrivate(QWorkbookAlignToolBar *q);
    virtual ~QWorkbookAlignToolBarPrivate() {}

    void setAlign(bool, Qt::Alignment);
    void setView(QObject *);
    void selectionChanged(FormatStatus*);

protected:
    QPushButton *pLeftBtn, *pHCentreBtn, *pRightBtn;
    QButtonGroup *pButtonGroup;
    QWorkbookAlignToolBar *q_ptr;
    QObject *pView;

    void init();
    void alignHasClicked();

};

class QWorkbookVerticalAlignToolBarPrivate : public AlignToolBarHelper {
    Q_DECLARE_PUBLIC(QWorkbookVerticalAlignToolBar)
public:
    QWorkbookVerticalAlignToolBarPrivate(QWorkbookVerticalAlignToolBar *q);
    virtual ~QWorkbookVerticalAlignToolBarPrivate() {}

    void setAlign(bool, Qt::Alignment);
    void setView(QObject *);
    void selectionChanged(FormatStatus*);

protected:
    QPushButton *pTopBtn, *pVCentreBtn, *pBottomBtn;
    QButtonGroup *pButtonGroup;
    QWorkbookVerticalAlignToolBar *q_ptr;
    QObject *pView;

    void init();
    void alignHasClicked();

};



}

#endif // QWORKBOOKALIGNTOOLBARPRIVATE_H
