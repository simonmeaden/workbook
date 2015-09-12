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

#include <cellreference.h>
#include <range.h>

class Worksheet;
class PluginStore;
class WorksheetModel;
class Cell;
class Format;


class WorksheetModelPrivate {
public:
    WorksheetModelPrivate(PluginStore *store, WorksheetModel *parent);
    WorksheetModelPrivate(Worksheet *sheet, PluginStore *store, WorksheetModel *parent);
    ~WorksheetModelPrivate();

    static const int INITIALCOLUMNS = 100;
    static const int INITIALROWS = 200;

    int rowCount() const ;
    int columnCount() const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    bool removeData(const QModelIndex &index, int role);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

    Format* format(const QModelIndex &index, int role = Qt::DisplayRole) const;
    Format* format(int row, int column, int role = Qt::DisplayRole) const;
    void setFormat(const QModelIndex &index, Format* format, int role = Qt::EditRole);
    void setFormat(int row, int column, Format* format, int role = Qt::EditRole) ;
    bool showGrid();

    bool isLocked(int row, int column);
    bool isLocked(CellReference &ref);

    void saveWorksheet(QString path);

    void setWorksheet(Worksheet *);
    void formatChanged(int , int );
    void formatHasChanged(Format*);
    void setShowGrid(bool );
    void lockCell(int , int );
    void lockCell(CellReference &);
    void lockRow(int &);
    void lockColumn(int &);
    void lockRange(Range &);
    void lockSheet();
    void unlockCell(int , int );
    void unlockCell(CellReference &);
    void unlockRow(int &);
    void unlockColumn(int &);
    void unlockRange(Range &);
    void unlockSheet();

    int maxRow();
    int maxColumn();


    Worksheet *pSheet;
    int mRows, mColumns;
    PluginStore *pPluginStore;
    SizeStatus mStatus;

    Q_DECLARE_PUBLIC(WorksheetModel)
    WorksheetModel *q_ptr;

};

#endif // WORKSHEETMODELPRIVATE_H
