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
#ifndef QWORKSHEETVIEW_H
#define QWORKSHEETVIEW_H

#include <QObject>
#include <QWidget>
#include <QTableView>
#include <QVariant>
#include <QVariantList>
#include <QScopedPointer>

#include <workbook_global.h>

#include "qworkbookview.h"
#include "cellreference.h"
#include "range.h"
#include "format.h"

class QWorksheetViewPrivate;
class WorksheetModel;
class PluginStore;
class WorkbookParser;
class Cell;

class WORKBOOKSHARED_EXPORT QWorksheetView : public QTableView {
    Q_OBJECT
public:
    QWorksheetView(QWidget *parent);
    ~QWorksheetView();


    QVariant read(int row, int column);
    QVariant read(const CellReference& reference);
    Format *format(int row, int column);
    Format *format(const CellReference& reference);

    QMap<QModelIndex, Format*> selectedFormats();

    QString sheetName();
    Worksheet* worksheet();

signals:
    void selectionChanged(FormatStatus*);

public slots:
    void setSheetName(QString);


    void write(int, int, QVariant);
    void write(const CellReference&, QVariant);
    void write(Range &, QVariant);

    void setFormat(int, int, Format*);
    void setFormat(const CellReference&, Format*);
    void setFormat(Range &, Format*);
    void setSelectedFormat(Format*);

    void setSelectionBold(bool);
    void setSelectionItalic(bool);
    void setSelectionUnderline(bool);
    void setSelectionFont(QFont);
    void setSelectionFontSize(int);
    void setSelectionAlignment(Qt::Alignment);
    void setSelectionMerge(bool);

    virtual void setSpan(int, int, int, int);

    void selectionHasChanged(const QItemSelection, const QItemSelection);
//    void currentCellChanged(const QModelIndex current, const QModelIndex previous);


private slots:
    void setModel(QAbstractItemModel *model);
    void setModel(WorksheetModel *model);

protected slots:
    virtual bool eventFilter(QObject *obj, QEvent *event);

protected:
    QWorksheetView(WorkbookParser *parser, PluginStore *store, QWidget *parent);

    QModelIndexList selectedIndexes();
    WorksheetModel* model();
    WorkbookParser *pParser;
    PluginStore *pPluginStore;


private:
    QScopedPointer<QWorksheetViewPrivate> d_ptr;
    Q_DECLARE_PRIVATE(QWorksheetView)

    friend class QWorkbookViewPrivate;
    friend class QWorkbookView;

};

#endif // WORKSHEETVIEW_H
