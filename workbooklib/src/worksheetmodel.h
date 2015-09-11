/*
 * This Workbook library is © Simon Meaden 2015. It is licensed under the LGPL V3 license.
 *
 * This Workbook library dynamically links to unmodified Nokia Qt5 Library. The Qt5
 * Library is © 2011 Nokia Corporation and/or its subsidiary(-ies), and is licensed
 * under the GNU Lesser General Public License version 2.1 with Nokia Qt LGPL exception
 * version 1.1.
 *
 * Qt5 library is free software; you can redistribute it and/or modify it under the
 * terms of the GNU Lesser General Public License, version 2.1, as published by the
 * Free Software Foundation.
 *
 * Qt5 library is provided “AS IS”, without WARRANTIES OR CONDITIONS OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED INCLUDING, WITHOUT LIMITATION, ANY WARRANTIES OR CONDITIONS OF
 * TITLE, NON-INFRINGEMENT, MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.
 *
 * As an additional permission to the GNU Lesser General Public License version 3.0, the
 * object code form of a “work that uses the Library” may incorporate material from a
 * header file that is part of the Library. You may distribute such object code under
 * terms of your choice, provided that: (i) the header files of the Library have not
 * been modified; and (ii) the incorporated material is limited to numerical parameters,
 * data structure layouts, accessors, macros, inline functions and templates; and (iii)
 * you comply with the terms of Section 6 of the GNU Lesser General Public License version 3.0.
 *
 * Moreover, you may apply this exception to a modified version of the Library, provided
 * that such modification does not involve copying material from the Library into the
 * modified Library’s header files unless such material is limited to (i) numerical
 * parameters; (ii) data structure layouts; (iii) accessors; and (iv) small macros,
 * templates and inline functions of five lines or less in length.
 *
 * Furthermore, you are not required to apply this additional permission to a modified
 * version of the Library.
 *
 * You should have received a copy of the GNU Lesser General Public License along
 * with this package; if not, write to the Free Software Foundation, Inc., 51 Franklin
 * Street, Fifth Floor, Boston, MA 02110-1301 USA
 *
 * The source code for Qt 5.4.X SDK is available from Nokia here:
 * http://get.qt.nokia.com/qt/source/qt-everywhere-opensource-src-4.7.X.zip.
 *
 * It is also available on request from Simon Meaden info@smelecomp.co.uk.
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
