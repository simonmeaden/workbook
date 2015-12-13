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
#ifndef MERGEDCELLPRIVATE_H
#define MERGEDCELLPRIVATE_H

#include <QObject>
#include <QVariant>

#include "types.h"
#include "cell.h"
#include "cell_p.h"

#include "workbook_global.h"

namespace QWorkbook {

class MergedCell;

class MergedCellPrivate : public CellPrivate {
//    Q_DECLARE_PUBLIC(MergedCell)
public:
    enum MergeType {
        MergedData,
        FirstCellData,
        NotMerged,
    };

    virtual ~MergedCellPrivate() {}

    QList<Cell*> overwritten() {
        return mOverwritten;
    }
    void setOverwritten(QList<Cell*> cells) {
        mOverwritten = cells;
    }
    void setMergedData() {
        mMergedData = MergedData;
    }
    void setFirstCell() {
        mMergedData = FirstCellData;
    }

    QList<Cell*> mOverwritten;
    MergeType mMergedData;

    int mRowSpan, mColSpan;


};


}

#endif // MERGEDCELLPRIVATE_H
