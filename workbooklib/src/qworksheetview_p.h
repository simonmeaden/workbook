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
#ifndef WORKSHEETVIEWPRIVATE_H
#define WORKSHEETVIEWPRIVATE_H

#include <QObject>
#include <QVariant>
#include <QItemSelection>
#include <QMessageBox>
#include <QList>
#include <QKeyEvent>

#include "cellreference.h"
#include "range.h"
#include "types.h"

class QWorksheetView;
class PluginStore;
class WorkbookParser;
class Format;
class Worksheet;


class QWorksheetViewPrivate {

    enum MergeStatus {
        MergePossible,
        DemergePossible,
        ContainsMerge,
    };

public:
    QWorksheetViewPrivate(QWorksheetView *parent);
    QWorksheetViewPrivate(WorkbookParser *parser, PluginStore *store, QWorksheetView *parent);
    virtual ~QWorksheetViewPrivate();

    WorkbookParser *pParser;
    PluginStore *pPluginStore;
    Worksheet *pSheet;

    QVariant read(int row, int column);
    QVariant read(const CellReference& reference);

    void write(int row, int column, QVariant item);
    void write(const CellReference& reference, QVariant item);
    void write(Range& range, QVariant item);

    Format* format(int row, int column);
    Format* format(const CellReference& reference);
    void setFormat(int row, int column, Format *format);
    void setSelectedFormat(Format *format);
    QMap<QModelIndex, Format*> selectedFormats();
    void setFormat(const CellReference& reference, Format *format);
    void setFormat(Range& range, Format *format);

    // toolbar interaction
    void setSelectionBold(bool);
    void setSelectionItalic(bool);
    void setSelectionUnderline(bool);
    void setSelectionFont(QFont);
    void setSelectionFontSize(int);
    void setSelectionAlignment(Qt::Alignment);
    void setSelectionMerge(bool);

    virtual void setSpan(int, int, int, int);
    virtual MergeStatus checkClearSpan(int, int, int, int);
    void mergeDataToFirstCell(int row, int column, int rowSpan, int colSpan);
    void firstCellRetainedRestStored(int row, int column, int rowSpan, int colSpan);

    bool eventFilter(QObject *obj, QEvent *event);
    void commitAndMove(QModelIndex &currentIndex, int &row, int &column);

    bool bContiguous;
    FormatStatus mFormatStatus;
    QModelIndexList mItems;
    void selectionHasChanged(QItemSelection, QItemSelection);

    void init();
    void setSheetName(QString);
    QString sheetName();
    Worksheet* worksheet();


    QWorksheetView*  const q_ptr;
    Q_DECLARE_PUBLIC(QWorksheetView)
};

#endif // WORKSHEETVIEWPRIVATE_H
