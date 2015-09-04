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

#ifndef WORKBOOKVIEW_H
#define WORKBOOKVIEW_H

#include <QWidget>
#include <QTabBar>
#include <QFrame>
#include <QStackedLayout>
#include <QGridLayout>
#include <QList>
#include <QTabWidget>
#include <QMenu>
#include <QAction>
#include <QEvent>
#include <QMouseEvent>
#include <QDialog>
#include <QAbstractItemDelegate>
#include <QDateTime>

#include <workbook_global.h>
#include "cellreference.h"
#include "range.h"
#include "format.h"
#include "types.h"

class Workbook;
class Worksheet;
class QWorkbookViewPrivate;
class QWorksheetView;
class WorkbookInsertSheetDialogPrivate;
class QWorkbookToolBar;
class Cell;

class WORKBOOKSHARED_EXPORT QWorkbookView : public QTabWidget {
    Q_OBJECT
    Q_PROPERTY(QString title READ title WRITE setTitle)
    Q_PROPERTY(QString subject READ subject WRITE setSubject)
    Q_PROPERTY(QString description READ description WRITE setDescription)
    Q_PROPERTY(QString keywords READ keywords WRITE setKeywords)
    Q_PROPERTY(QString creator READ creator WRITE setCreator)
    Q_PROPERTY(QString comments READ comments WRITE setComments)
    Q_PROPERTY(QString category READ category WRITE setCategory)
    Q_PROPERTY(QDateTime created READ created WRITE setCreated)
public:
    QWorkbookView(QWidget *parent);
    ~QWorkbookView();

    QWorkbookToolBar* toolBar();
    int indexOf(Worksheet*);
    QWorksheetView* addWorksheet();
    QWorksheetView* addWorksheet(QString name);
    QWorksheetView* insertWorksheet(int position);
    QWorksheetView* insertWorksheet(int position, QString name);

    QVariant read(int row, int column);
    QVariant read(const CellReference& reference);
    QVariant read(int index, int row, int column);
    QVariant read(int index, const CellReference& reference);
    QVariant read(QString name, int row, int column);
    QVariant read(QString name, const CellReference& reference);

    Format* format(int row, int column);
    Format* format(const CellReference& reference);
    Format* format(int index, int row, int column);
    Format* format(int index, const CellReference& reference);
    Format* format(int index, const Range& range);
    Format* format(QString name, int row, int column);
    Format* format(QString name, const CellReference& reference);

    QMap<QModelIndex, Format*> selectedFormats();
    QMap<QModelIndex, Format*> selectedFormats(int index);
    QMap<QModelIndex, Format*> selectedFormats(QString name);

    bool showGrid();
    bool showGrid(int index);
    bool showGrid(QString name);

    QString title();
    void setTitle(QString title);
    QString subject();
    void setSubject(QString subject);
    QString description();
    void setDescription(QString description);
    QString keywords();
    void setKeywords(QString keywords);
    QString comments();
    void setComments(QString comments);
    QString creator();
    void setCreator(QString creator);
    QString company();
    void setCompany(QString company);
    QDateTime created();
    void setCreated(QDateTime created);
    QString category();
    void setCategory(QString category);



signals:
    void selectionChanged(FormatStatus*);

public slots:
    void setWorkbook(Workbook *book);
    void setCurrentWorksheet(int index);
    void setCurrentWorksheet(QString name);
    void saveWorkbook(QString filename);
    void saveWorkbook(QString filename, WorksheetType type);
    void removeWorksheet(int position);
    void removeWorksheet(Worksheet *sheet);
    void removeWorksheet(QString name);
    void renameSheet(QString oldname, QString newname);
    void setTabText(int index, QString text);

    void triggerInitialSelection();

    void write(int row, int column, QVariant item);
    void write(CellReference& reference, QVariant item);
    void write(Range& range, QVariant item);
    void write(int index, int row, int column, QVariant item);
    void write(int index, CellReference& reference, QVariant item);
    void write(int index, Range &range, QVariant item);
    void write(QString name, int row, int column, QVariant item);
    void write(QString name, CellReference& reference, QVariant item);
    void write(QString name, Range &range, QVariant item);

    void writeImage(int row, int column, QString path);
    void writeImage(CellReference& reference, QString path);
    void writeImage(int index, int row, int column, QString path);
    void writeImage(int index, CellReference& reference, QString path);
    void writeImage(QString name, int row, int column, QString path);
    void writeImage(QString name, CellReference& reference, QString path);

    void writeImage(int row, int column, QImage path);
    void writeImage(CellReference& reference, QImage path);
    void writeImage(int index, int row, int column, QImage path);
    void writeImage(int index, CellReference& reference, QImage path);
    void writeImage(QString name, int row, int column, QImage path);
    void writeImage(QString name, CellReference& reference, QImage path);

    void setFormat(int row, int column, Format *item);
    void setFormat(const CellReference& reference, Format *item);
    void setFormat(Range &range, Format *item);
    void setFormat(int index, int row, int column, Format *item);
    void setFormat(int index, const CellReference& reference, Format *item);
    void setFormat(int index, Range& range, Format *item);
    void setFormat(QString name, int row, int column, Format *item);
    void setFormat(QString name, const CellReference& reference, Format *item);
    void setFormat(QString name, Range& range, Format *item);

    void setSelectedFormat(Format *format);
    void setSelectedFormat(int index, Format *format);
    void setSelectedFormat(QString name, Format *format);

    void setShowGrid(bool showGrid);
    void setShowGrid(int index, bool showGrid);
    void setShowGrid(QString name, bool showGrid);

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

    void lockCell(int index, int row, int column);
    void lockCell(int index, CellReference &ref);
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
    void lockCell(QString name, CellReference &ref);
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


protected slots:
//    virtual void closeEditor(QWidget* editor, QAbstractItemDelegate::EndEditHint hint);
//    virtual void keyPressEvent(QKeyEvent* event);
    virtual void setCurrentWidget(QWidget *widget);
    virtual void removeTab(int index);

    void showContextMenu(const QPoint &point);

    // context menu methods.
    void insertSheet();
    void renameSheet();
    void moveCopySheet();
    void protectSheet();
    void tabColor();

    // toolbar methods
    void setSelectionBold(bool);
    void setSelectionItalic(bool);
    void setSelectionUnderline(bool);
    void setSelectionFont(QFont);
    void setSelectionFontSize(int);
    void setSelectionAlignment(Qt::Alignment);
    void setSelectionMerge(bool);
    void indentCells();
    void undentCells();
    void setFont(QFont);

protected:
    Worksheet* currentWorksheet();
    QWorksheetView* currentWorksheetView();

private:
    QWorkbookViewPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QWorkbookView)

    virtual QWidget* currentWidget() const;
    virtual int addTab(QWidget*widget, const QString&label);
    virtual int addTab(QWidget*widget, const QIcon&icon, const QString&label);
    virtual int insertTab (int index, QWidget*widget, const QString&label);
    virtual int insertTab (int index, QWidget*widget, const QIcon&icon, const QString&label);
    virtual QWidget* widget(int index) const;

};

#endif // WORKBOOKVIEW_H
