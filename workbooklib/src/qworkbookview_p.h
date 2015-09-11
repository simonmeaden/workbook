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
#ifndef WORKBOOKVIEWPRIVATE_H
#define WORKBOOKVIEWPRIVATE_H

#include <QObject>
#include <QTabBar>
#include <QStackedLayout>
#include <QFrame>
#include <QGridLayout>
#include <QDialog>
#include <QPushButton>
#include <QCheckBox>
#include <QLabel>
#include <QSpinBox>
#include <QButtonGroup>
#include <QLineEdit>
#include <QVariant>
#include <QDateTime>
#include <QItemSelectionModel>

#include "cellreference.h"
#include "range.h"
#include "types.h"

class QWorkbookView;
class QWorksheetView;
class Workbook;
class Worksheet;
class WorkbookInsertSheetDialog;
class WorksheetModel;
class Format;
class PluginStore;
class WorkbookParser;
class QWorkbookToolBar;

class QWorkbookViewPrivate {

public:
    QWorkbookViewPrivate(QWorkbookView *parent);
    ~QWorkbookViewPrivate();

    // document properties
    QString sTitle, sSubject, sDescription, sKeywords, sComments, sCreator, sCompany, sCategory;
    QDateTime mCreated;
    QString title() { return sTitle; }
    void setTitle(QString title) { sTitle = title; }
    QString subject() { return sSubject; }
    void setSubject(QString subject) { sSubject = subject; }
    QString description() { return sDescription; }
    void setDescription(QString description) { sDescription = description; }
    QString keywords() { return sKeywords; }
    void setKeywords(QString keywords) { sKeywords = keywords; }
    QString comments() { return sComments; }
    void setComments(QString comments) { sComments = comments; }
    QString category() { return sCategory; }
    void setCategory(QString category) { sCategory = category; }
    QString creator() { return sCreator; }
    void setCreator(QString creator) { sCreator = creator; }
    QString company() { return sCompany; }
    void setCompany(QString company) { sCompany = company; }
    QDateTime created() { return mCreated; }
    void setCreated(QDateTime created) { mCreated = created; }

    void createActions();
    QWorkbookToolBar* toolBar();

    bool showGrid();
    bool showGrid(int index);
    bool showGrid(QString name);
    void setShowGrid(bool showGrid);
    void setShowGrid(int index, bool showGrid);
    void setShowGrid(QString name, bool showGrid);

    QVariant read(int row, int column);
    QVariant read(int index, int row, int column);
    QVariant read(QString name, int row, int column);

    void write(int row, int column, QVariant item);
    void write(int index, int row, int column, QVariant item);
    void write(QString name, int row, int column, QVariant item);
    void write(Range& range, QVariant item);
    void write(int index, Range &range, QVariant item);
    void write(QString name, Range &range, QVariant item);

    void writeImage(int row, int column, QString path);
    void writeImage(int index, int row, int column, QString path);
    void writeImage(QString name, int row, int column, QString path);

    void writeImage(int row, int column, QImage image);
    void writeImage(int index, int row, int column, QImage image);
    void writeImage(QString name, int row, int column, QImage image);

    QImage imageFromFilename(QString path);

    Format* format(int row, int column);
    Format* format(int index, int row, int column);
    Format* format(QString name, int row, int column);
    void setFormat(int row, int column, Format *item);
    void setFormat(int index, int row, int column, Format *item);
    void setFormat(QString name, int row, int column, Format *item);
    void setFormat(Range &range, Format *item);
    void setFormat(int index, Range& range, Format *item);
    void setFormat(QString name, Range& range, Format *item);

    QMap<QModelIndex, Format*> selectedFormats();
    QMap<QModelIndex, Format*> selectedFormats(int index);
    QMap<QModelIndex, Format*> selectedFormats(QString name);
    void setSelectedFormat(Format *format);
    void setSelectedFormat(int index, Format *format);
    void setSelectedFormat(QString name, Format *format);

    void lockCell(int row, int column);
    void lockRow(int &row);
    void lockColumn(int &column);
    void lockRange(Range &range);
    void lockSheet();
    void unlockCell(int row, int column);
    void unlockRow(int &row);
    void unlockColumn(int &column);
    void unlockRange(Range &range);
    void unlockSheet();

    void lockCell(int index, int row, int column);
    void lockRow(int index, int &row);
    void lockColumn(int index, int &column);
    void lockRange(int index, Range &range);
    void lockSheet(int index);
    void unlockCell(int index, int row, int column);
    void unlockCell(int index, CellReference &ref);
    void unlockRow(int index, int &row);
    void unlockColumn(int index, int &column);
    void unlockRange(int index, Range &range);
    void unlockSheet(int index);

    void lockCell(QString name, int row, int column);
    void lockRow(QString name, int &row);
    void lockColumn(QString name, int &column);
    void lockRange(QString name, Range &range);
    void lockSheet(QString name);
    void unlockCell(QString name, int row, int column);
    void unlockCell(QString name, CellReference &ref);
    void unlockRow(QString name, int &row);
    void unlockColumn(QString name, int &column);
    void unlockRange(QString name, Range &range);
    void unlockSheet(QString name);

    int indexOf(Worksheet*);
    QWorksheetView *addWorksheet();
    QWorksheetView *addWorksheet(QString name);
    QWorksheetView *insertWorksheet(int position);
    QWorksheetView* insertWorksheet(int position, QString name);
    QWorksheetView *initWorksheet();
    void removeWorksheet(int position);
    void removeWorksheet(Worksheet *sheet);
    void removeWorksheet(QString name);

    QWorksheetView* currentWorksheetView();
    Worksheet* currentWorksheet();
    void setCurrentWorksheet(int index);
    void setCurrentWorksheet(QString name);

    void saveWorkbook(QString filename);
    void saveWorkbook(QString filename, WorksheetType type);

    QWorksheetView* worksheetview(int index);
    QWorksheetView* worksheetview(QString name);

    void renameSheet(QString oldname, QString newname);
    void setTabText(int index, QString text);

    Workbook* book() {return pBook; }
    void setWorkbook(Workbook *book);

//    void closeEditor(QWidget* editor, QAbstractItemDelegate::EndEditHint hint);
//    void keyPressEvent(QKeyEvent* event);

    // popup menu for tabs
    QAction *pInsertSheetAction, *pRenameSheetAction, *pMoveCopySheetAction;
    QAction *pProtectSheetAction, *pTabColorAction;
    bool bEnableContextMenu, pEnableTabMenu;
    int mCurrentIndex;
    QWorksheetView *pCurrentView;

    void enablePopup();
    void insertSheet();
    void renameSheet();
    void moveCopySheet();
    void protectSheet();
    void tabColor();
    void showContextMenu(const QPoint &point);
    void enableContextMenu(bool);
    void enableTabMenu(bool);

    // toolbar methods
    void triggerInitialSelection();
    void alignmentHasChanged(Qt::Alignment);
    void setSelectionBold(bool);
    void setSelectionItalic(bool);
    void setSelectionUnderline(bool);
    void setSelectionFont(QFont);
    void setSelectionFontSize(int);
    void setSelectionAlignment(Qt::Alignment);
    void setSelectionMerge(bool);
    void setFont(QFont);
    void indentCells();
    void undentCells();

protected:
    QTabBar *pTabBar;
    WorkbookParser *pParser;
    PluginStore *pPluginStore;
    static quint8 sheetNumber;

private:
    Workbook *pBook;
    QWorkbookView *q_ptr;
    Q_DECLARE_PUBLIC(QWorkbookView)
};

#endif // WORKBOOKVIEWPRIVATE_H
