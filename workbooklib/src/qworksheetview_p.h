/*
    This Workbook library is © Simon Meaden 2015. It is licensed under the LGPL V3 license.

    This Workbook library dynamically links to unmodified Nokia Qt5 Library. The Qt5
    Library is © 2011 Nokia Corporation and/or its subsidiary(-ies), and is licensed
    under the GNU Lesser General Public License version 2.1 with Nokia Qt LGPL exception
    version 1.1.

    Qt5 library is free software; you can redistribute it and/or modify it under the
    terms of the GNU Lesser General Public License, version 2.1, as published by the
    Free Software Foundation.

    Qt5 library is provided “AS IS”, without WARRANTIES OR CONDITIONS OF ANY KIND, EITHER
    EXPRESS OR IMPLIED INCLUDING, WITHOUT LIMITATION, ANY WARRANTIES OR CONDITIONS OF
    TITLE, NON-INFRINGEMENT, MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.

    As an additional permission to the GNU Lesser General Public License version 3.0, the
    object code form of a “work that uses the Library” may incorporate material from a
    header file that is part of the Library. You may distribute such object code under
    terms of your choice, provided that: (i) the header files of the Library have not
    been modified; and (ii) the incorporated material is limited to numerical parameters,
    data structure layouts, accessors, macros, inline functions and templates; and (iii)
    you comply with the terms of Section 6 of the GNU Lesser General Public License version 3.0.

    Moreover, you may apply this exception to a modified version of the Library, provided
    that such modification does not involve copying material from the Library into the
    modified Library’s header files unless such material is limited to (i) numerical
    parameters; (ii) data structure layouts; (iii) accessors; and (iv) small macros,
    templates and inline functions of five lines or less in length.

    Furthermore, you are not required to apply this additional permission to a modified
    version of the Library.

    You should have received a copy of the GNU Lesser General Public License along
    with this package; if not, write to the Free Software Foundation, Inc., 51 Franklin
    Street, Fifth Floor, Boston, MA 02110-1301 USA

    The source code for Qt 5.4.X SDK is available from Nokia here:
    http://get.qt.nokia.com/qt/source/qt-everywhere-opensource-src-4.7.X.zip.

    It is also available on request from Simon Meaden info@smelecomp.co.uk.
*/
#ifndef WORKSHEETVIEWPRIVATE_H
#define WORKSHEETVIEWPRIVATE_H

#include <QObject>
#include <QVariant>
#include <QItemSelection>
#include <QMessageBox>

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
