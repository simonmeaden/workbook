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
#ifndef WORKSHEETMODELPRIVATE_H
#define WORKSHEETMODELPRIVATE_H

#include <QVariant>
#include <QModelIndex>
#include <QList>
#include <QScopedPointer>

#include "workbook_global.h"
#include "cellreference.h"
#include "reference.h"
#include "range.h"
#include "types.h"

namespace QXlsx {
    class Worksheet;
}

namespace ods {
    class Sheet;
}

namespace QWorkbook {

class WorksheetModel;
class PluginStore;
class Cell;
class Format;


class WorksheetModelPrivate : public Reference {
    Q_DECLARE_PUBLIC(WorksheetModel)
public:
    WorksheetModelPrivate(WorksheetModel *parent);
    virtual ~WorksheetModelPrivate() {}

    static const int INITIALCOLUMNS = 100;
    static const int INITIALROWS = 200;

    int rowCount() const ;
    int columnCount() const;
    QModelIndex getIndex(int, int);
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(QModelIndex&, const QVariant, int);
    bool removeData(const QModelIndex&, int);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

    Format* format(const QModelIndex &index, int role = Qt::DisplayRole) const;
    void setFormat(const QModelIndex &index, Format* format, int role = Qt::EditRole);
    void setFormat(int row, int column, Format* format, int role = Qt::EditRole) ;

    bool isLocked(int row, int column);
    bool isLocked(CellReference &ref);

    void saveWorksheet(QString path, WorksheetType type);

    WorksheetModel *clone();
//    void setWorksheet(Worksheet *sheet);

    void formatChanged(QModelIndex index);
    void formatHasChanged(Format*);
    void lockCell(QModelIndex index);
    void lockCell(int , int);
    void lockCell(CellReference &);
    void lockRow(int &);
    void lockColumn(int &);
    void lockRange(Range &);
    void lockSheet();
    void unlockCell(QModelIndex);
    void unlockCell(int, int);
    void unlockCell(CellReference &);
    void unlockRow(int &);
    void unlockColumn(int &);
    void unlockRange(Range &);
    void unlockSheet();
    Cell* cellAsCell(int row, int column);
    void setCellAsCell(int, int, Cell*);

    void readXlsx();
    void writeXlsx(QString path);
    void writeXlsx(QXlsx::Worksheet *sheet);

    void readOds();
    void writeOds(QString path);
    void writeOds(ods::Sheet *sheet);

    int maxRow();
    int maxColumn();

    void setSheetName(QString);
    QString sheetName();

    SizeStatus mStatus;

    bool bSheetLocked;
    QString mSheetName;
    QMap<QModelIndex, Cell*> mCellData;
    QMap<QModelIndex, Format*> mCellFormat;
    QMap<int, bool> mRowLocked;
    QMap<int, bool> mColLocked;
    QMap<int, Format*> mRowFormat;
    QMap<int, Format*> mColFormat;

    WorksheetModel *q_ptr;

};


}

#endif // WORKSHEETMODELPRIVATE_H
