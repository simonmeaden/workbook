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
#include <QScopedPointer>

#include "cellreference.h"
#include "range.h"
#include "format.h"
#include "types.h"
#include "toolbar/qcelledittoolbar.h"
#include "qworkbookview_p.h"

#include "workbook_global.h"

namespace QWorkbook {

class Workbook;
class QWorksheetView;
class WorkbookInsertSheetDialogPrivate;
class QWorkbookToolBar;
class QCellEditToolBar;
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
    Q_DECLARE_PRIVATE(QWorkbookView)
public:
    QWorkbookView(QWidget *parent);
    virtual ~QWorkbookView() {}

    QWorkbookToolBar* toolBar();
    QCellEditToolBar* editBar();
    int indexOf(QWorksheetView *);
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

    QStringList names();

signals:
    void selectionChanged(FormatStatus*);
    void cellChanged(QVariant);
    void cellContentsChanged(QString); // called by cell editor when cell contents change before commit.

public slots:

    void enableMovableTabs(bool);
    void enableContextMenu(bool);
    void enableTabMenu(bool);

    void setCurrentWorksheetView(int index);
    void setCurrentWorksheetView(QString name);
    void saveWorkbook(QString filename);
    void saveWorkbook(QString filename, WorksheetType type);
    void removeWorksheet(int position);
    void removeWorksheet(QWorksheetView *sheet);
    void removeWorksheet(QString name);
    void renameSheet(QString oldname, QString newname);
    void setTabText(int index, QString text);

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
    void insertSheetBefore();
    void insertSheetAfter();
    void renameSheet();
    void deleteSheet();
    void moveCopySheet();
    void protectSheet();
    void tabColor();

    // toolbar methods
    void changeCellContents(QString text);
    void triggerInitialSelection();
    void triggerCurrentSelection();
    void setSelectionBold(bool);
    void setSelectionItalic(bool);
    void setSelectionUnderline(bool);
    void setSelectionFont(QFont);
    void setSelectionFontSize(int);
    void setSelectionAlignment(Qt::Alignment);
    void setSelectionMerge();
    void indentCells();
    void undentCells();
    void setFont(QFont);

protected:
    QWorksheetView *currentWorksheetView();

private:
    QScopedPointer<QWorkbookViewPrivate> d_ptr;

    virtual QWidget* currentWidget() const;
    virtual int addTab(QWidget*widget, const QString&label);
    virtual int addTab(QWidget*widget, const QIcon&icon, const QString&label);
    virtual int insertTab (int index, QWidget*widget, const QString&label);
    virtual int insertTab (int index, QWidget*widget, const QIcon&icon, const QString&label);
    virtual QWidget* widget(int index) const;

    friend class QWorkbookToolBarPrivate;
    friend class QCellEditToolBarPrivate;
    friend class WorkbookParserPrivate;
    friend class WorkbookPrivate;

};


}

#endif // WORKBOOKVIEW_H
