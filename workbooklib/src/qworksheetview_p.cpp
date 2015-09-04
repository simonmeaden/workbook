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
#include "qworksheetview_p.h"
#include "qworksheetview.h"
#include "formatdelegate.h"
#include "worksheetmodel.h"

#include "pluginstore.h"
#include "workbookparser.h"
#include <qstd.h>

QWorksheetViewPrivate::QWorksheetViewPrivate(QWorksheetView *parent) :
    q_ptr(parent) {

    pPluginStore = new PluginStore(q_ptr);
    pParser = new WorkbookParser(pPluginStore, q_ptr);

    init();

}

QWorksheetViewPrivate::QWorksheetViewPrivate(WorkbookParser *parser, PluginStore *store, QWorksheetView *parent) :
    pParser(parser),
    pPluginStore(store),
    q_ptr(parent) {

    init();

}

QWorksheetViewPrivate::~QWorksheetViewPrivate() {

}

void QWorksheetViewPrivate::init() {

    pSheet = new Worksheet(pPluginStore, q_ptr);
    q_ptr->setModel(new WorksheetModel(pSheet, pPluginStore, q_ptr));
    q_ptr->setItemDelegate(new FormatDelegate(q_ptr));

    bContiguous = true;

    q_ptr->setSelectionMode(QTableView::ExtendedSelection);

    QItemSelectionModel *sm = q_ptr->selectionModel();
    q_ptr->connect(sm,
                   SIGNAL(selectionChanged(QItemSelection, QItemSelection)),
                   q_ptr,
                   SLOT(selectionHasChanged(QItemSelection, QItemSelection)));

}

Worksheet* QWorksheetViewPrivate::worksheet() {
    return pSheet;
}

void QWorksheetViewPrivate::setSheetName(QString name) {
    pSheet->setSheetName(name);
}

QString QWorksheetViewPrivate::sheetName() {
    return pSheet->sheetName();
}


void QWorksheetViewPrivate::selectionHasChanged(QItemSelection selected, QItemSelection /*deselected*/) {
//    QModelIndex index;

    Q_Q(QWorksheetView);

    mFormatStatus.clear();

    mItems = selected.indexes();
    QList<Format*> formats;
    Format* format;
    int row, col;

    foreach (QModelIndex index, mItems) {
        row = index.row();
        col = index.column();
        mFormatStatus.mCount++;
        mFormatStatus.mMinRow = (row < mFormatStatus.mMinRow ? row : mFormatStatus.mMinRow);
        mFormatStatus.mMaxRow = (row > mFormatStatus.mMaxRow ? row : mFormatStatus.mMaxRow);
        mFormatStatus.mMinCol = (col < mFormatStatus.mMinCol ? col : mFormatStatus.mMinCol);
        mFormatStatus.mMaxCol = (col > mFormatStatus.mMaxCol ? col : mFormatStatus.mMaxCol);

        if (index.isValid()) {
            format = q_ptr->model()->format(index);
            formats.append(format);
        }

    }

    if (((mFormatStatus.mMaxRow - mFormatStatus.mMinRow) * (mFormatStatus.mMaxCol - mFormatStatus.mMinCol)) > mFormatStatus.mCount)
        mFormatStatus.bContiguous = false;
    else
        mFormatStatus.bContiguous = true;

    bContiguous = mFormatStatus.bContiguous;

    cout << (bContiguous ? "contiguous" : "non-contiguous") << endl << flush;

    if (formats.size() == 0) {
        emit q->selectionChanged(NULL);
        return;
    }


    format = formats.at(0);
    QFont font = format->font();
    int fontSize = font.pointSize();
    bool bold = format->bold();
    bool italic = format->italic();
    bool underline = format->underline();
    Qt::Alignment alignment = format->alignment();
    Format::UnderlineStyle uStyle = format->underlineStyle();
    QColor uColor = format->underlineColor();
    bool overline = format->overline();
    bool strikeout = format->strikeout();

    mFormatStatus.bAllBold = !bold;
    mFormatStatus.bAllItalic = !italic;
    mFormatStatus.bAllOverline = !overline;
    mFormatStatus.bAllStrikeout = !strikeout;
    mFormatStatus.bAllUnderline = !underline;
//    mFormatStatus.bAllUnderline = (uStyle == format->underlineStyle());
//    mFormatStatus.bAllUnderline = (uColor == format->underlineColor());
    mFormatStatus.bAllSameFont = (font == format->font());
//    mFormatStatus.bAllSameAlignment = true; // already done

    for(int i = 1; i < formats.size(); i++) {
        format = formats.at(i);

        if (mFormatStatus.bAllBold)
            if (bold != format->bold())
                mFormatStatus.bAllBold = false;

        if (mFormatStatus.bAllItalic)
            if (italic != format->italic())
                mFormatStatus.bAllItalic = false;

        if (mFormatStatus.bAllOverline)
            if (overline != format->overline())
                mFormatStatus.bAllOverline = false;

        if (mFormatStatus.bAllStrikeout)
            if (strikeout != format->strikeout())
                mFormatStatus.bAllStrikeout = false;

        if (mFormatStatus.bAllUnderline)
            if (underline != format->underline())
                mFormatStatus.bAllUnderline = false;

        if (mFormatStatus.bAllUnderline)
            if (uStyle != format->underlineStyle())
                mFormatStatus.bAllUnderline = false;

        if (mFormatStatus.bAllUnderline)
            if (uColor != format->underlineColor())
                mFormatStatus.bAllUnderline = false;

        if (mFormatStatus.bAllSameFont)
            if (font != format->font())
                mFormatStatus.bAllSameFont = false;

        if (mFormatStatus.bAllSameAlignment)
            if (alignment != format->alignment())
                mFormatStatus.bAllSameAlignment = false;

        if (mFormatStatus.allSet()) break;
    }

    if (mFormatStatus.bAllSameFont) {
        mFormatStatus.mFont = font;
        mFormatStatus.mFontSize = fontSize;
    }

    if (mFormatStatus.bAllSameAlignment) {
        mFormatStatus.mAlignment = alignment;
    }

    emit q->selectionChanged(&mFormatStatus);

}

void QWorksheetViewPrivate::setSelectionBold(bool value) {

    Format* format;
    int row, col;

    foreach (QModelIndex index, mItems) {

        if (index.isValid()) {
            row = index.row();
            col = index.column();

            format = q_ptr->model()->format(index);
            format->setBold(value);
            q_ptr->setFormat(row, col, format);
        }

    }
}

void QWorksheetViewPrivate::setSelectionItalic(bool value) {

    Format* format;
    int row, col;

    foreach (QModelIndex index, mItems) {

        if (index.isValid()) {
            row = index.row();
            col = index.column();

            format = q_ptr->model()->format(index);
            format->setItalic(value);
            q_ptr->setFormat(row, col, format);
        }

    }
}

void QWorksheetViewPrivate::setSelectionUnderline(bool value) {

    Format* format;
    int row, col;

    foreach (QModelIndex index, mItems) {

        if (index.isValid()) {
            row = index.row();
            col = index.column();

            format = q_ptr->model()->format(index);
            format->setUnderline(value);
            q_ptr->setFormat(row, col, format);
        }

    }
}

void QWorksheetViewPrivate::setSelectionFont(QFont font) {

    Format* format;
    int row, col;

    foreach (QModelIndex index, mItems) {

        if (index.isValid()) {
            row = index.row();
            col = index.column();

            format = q_ptr->model()->format(index);
            format->setFont(font);
            cout << font.family() << " : " << font.pointSize() << endl << flush;
            q_ptr->setFormat(row, col, format);
        }

    }
}

void QWorksheetViewPrivate::setSelectionFontSize(int size) {

    Format* format;
    int row, col;

    foreach (QModelIndex index, mItems) {

        if (index.isValid()) {
            row = index.row();
            col = index.column();

            format = q_ptr->model()->format(index);
            format->setPointSize(size);
            q_ptr->setFormat(row, col, format);
        }

    }
}

void QWorksheetViewPrivate::setSelectionAlignment(Qt::Alignment alignment) {

    Format* format;
    int row, col;

    foreach (QModelIndex index, mItems) {

        if (index.isValid()) {
            row = index.row();
            col = index.column();

            format = q_ptr->model()->format(index);
            format->setAlignment(alignment);
            q_ptr->setFormat(row, col, format);
        }

    }
}
void QWorksheetViewPrivate::setSelectionMerge(bool merge) {
    if (merge) {
        if (bContiguous) {
            int row = mFormatStatus.mMinRow;
            int col = mFormatStatus.mMinCol;
            int rowSpan = mFormatStatus.mMaxRow - mFormatStatus.mMinRow;
            int colSpan = mFormatStatus.mMaxCol - mFormatStatus.mMinCol;
            q_ptr->setSpan(row, col, rowSpan, colSpan);
        }
    }
}

QVariant QWorksheetViewPrivate::read(int row, int column) {

    QModelIndex index = q_ptr->model()->index(row, column);
    if (index.isValid())
        return q_ptr->model()->data(index);

    return QVariant();
}


QVariant QWorksheetViewPrivate::read(const CellReference& reference) {
    int row = reference.row();
    int column = reference.column();
    return read(row, column);
}

void QWorksheetViewPrivate::write(int row, int column, QVariant item) {
    QModelIndex index = q_ptr->model()->index(row, column);
    if (index.isValid())
        q_ptr->model()->setData(index, item, Qt::EditRole);
}

void QWorksheetViewPrivate::write(const CellReference& reference, QVariant item) {
    int row = reference.row();
    int column = reference.column();
    write(row, column, item);
}

void QWorksheetViewPrivate::write(Range& range, QVariant item) {
    for (int row = range.top(); row <= range.bottom(); row++) {
        for (int col = range.left(); col <= range.right(); col++) {
            write(row, col, item);
        }
    }
}

Format* QWorksheetViewPrivate::format(int row, int column) {
    QModelIndex index = q_ptr->model()->index(row, column);
    if (index.isValid())
        return q_ptr->model()->format(index);

    return NULL;
}

Format* QWorksheetViewPrivate::format(const CellReference& reference) {
    int row = reference.row();
    int column = reference.column();
    return format(row, column);
}

void QWorksheetViewPrivate::setFormat(int row, int column, Format *format) {
    QModelIndex index = q_ptr->model()->index(row, column);
    if (index.isValid())
        q_ptr->model()->setFormat(index, format, Qt::EditRole);

}

void QWorksheetViewPrivate::setSelectedFormat(Format *format) {
    QModelIndexList list = q_ptr->selectedIndexes();
    QListIterator<QModelIndex> it(list);
    while(it.hasNext()) {
        QModelIndex index = it.next();
        if (index.isValid())
            setFormat(index.row(), index.column(), format);
    }
}

QMap<QModelIndex, Format*> QWorksheetViewPrivate::selectedFormats() {
    QMap<QModelIndex, Format*> formats;

    QModelIndexList list = q_ptr->selectedIndexes();
    QListIterator<QModelIndex> it(list);
    while(it.hasNext()) {
        QModelIndex index = it.next();
        if (index.isValid())
            formats.insert(index, format(index.row(), index.column()));
    }
    return formats;
}

void QWorksheetViewPrivate::setFormat(const CellReference& reference, Format *format) {
    int row = reference.row();
    int column = reference.column();

    QModelIndex index = q_ptr->model()->index(row, column);
    if (index.isValid())
        q_ptr->model()->setFormat(index, format, Qt::EditRole);

}

void QWorksheetViewPrivate::setFormat(Range& range, Format *format) {
    for (int row = range.top(); row <= range.bottom(); row++) {
        for (int col = range.left(); col <= range.right(); col++) {
            setFormat(row, col, format);
        }
    }
}
