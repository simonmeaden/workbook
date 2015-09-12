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
#ifndef WORKSHEETVIEWMODEL_H
#define WORKSHEETVIEWMODEL_H

#include <QAbstractTableModel>
#include <QVariant>
#include <QModelIndex>
#include <QObject>
#include <QScopedPointer>

#include "pluginstore.h"

class Worksheet;
class Format;
class Range;
class CellReference;
class Cell;
class WorksheetModelPrivate;


class WorksheetModel : public QAbstractTableModel {
    Q_OBJECT
public:
    WorksheetModel(PluginStore *store, QObject *parent);
    WorksheetModel(Worksheet *sheet, PluginStore *store, QObject *parent);
    ~WorksheetModel();

    static const int COLUMNS = 100;
    static const int ROWS = 200;

    int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
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

    int maxRow();
    int maxColumn();

public slots:
    void setWorksheet(Worksheet *sheet);
    void formatChanged(int row, int column);
    void formatHasChanged(Format*);
    void setShowGrid(bool showGrid);
    void lockCell(int row, int column);
    void lockCell(CellReference &ref);
    void lockRow(int &row);
    void lockColumn(int &column);
    void lockRange(Range &range);
    void lockSheet();
    void unlockCell(int row, int column);
    void unlockCell(CellReference &ref);
    void unlockRow(int &row);
    void unlockColumn(int &column);
    void unlockRange(Range &range);
    void unlockSheet();
//    void span(int, int, int, int , QList<Cell *> = QList<Cell*>());
//    void despan(int, int, int, int );

protected:
    QScopedPointer<WorksheetModelPrivate> d_ptr;

    Cell* cellAsCell(int, int);

protected slots:
    void setCellAsCell(int, int, Cell*);

private:
    Q_DECLARE_PRIVATE(WorksheetModel)


    friend class QWorksheetViewPrivate;
};

#endif // WORKSHEETVIEWMODEL_H
