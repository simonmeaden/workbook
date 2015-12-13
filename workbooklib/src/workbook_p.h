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
#ifndef WORKBOOKPRIVATE_H
#define WORKBOOKPRIVATE_H

#include <QObject>
#include <QMap>
#include <QList>
#include <QFileDialog>

#include "types.h"
#include "pluginstore.h"
#include "workbookparser.h"

#include "workbook_global.h"

namespace QWorkbook {

class Workbook;
class QWorkbookView;
class QWorkbookToolBar;
class QWorksheetView;
class WorkbookParser;

class WorkbookPrivate {
public:
    WorkbookPrivate(PWorkbookParser parser,
                    QWorkbookView *bookView,
                    Workbook *parent);
    virtual ~WorkbookPrivate() {}

    QWorksheetView* worksheetView(int index);
    QWorksheetView* worksheetView(QString name);
    QWorksheetView* currentWorksheetView();
    void setCurrentWorksheetView(int index);
    void setCurrentWorksheetView(QString name);
    QWorksheetView *addWorksheet();
    QWorksheetView *insertWorksheet(int index, QWorksheetView *view);
    QWorksheetView* insertNewWorksheet(int index);
    int indexOf(QWorksheetView *);
    int size() { return mSheets.size(); }

    int removeWorksheet(int index);
    int removeWorksheet(QString name);
    int removeWorksheet(QWorksheetView *sheet);

    int renameSheet(QString oldname, QString newname);
    void moveSheet(int oldIndex, int newIndex);

    void saveWorkbook(QString filename, WorksheetType type);
    void saveOds(QString filename);
    void saveCSV(QString filename);
    void saveDif(QString filename);
    void saveXls(QString filename);
    void saveXlsx(QString filename);
    void loadWorkbook(QString filename);

    void setToolbar(QWorkbookToolBar *pToolbar);

    QStringList names();

protected:
    void renameSheets(int index);
    bool areNumbers(QString str);
    bool isRealName(QString str);

    QWorkbookView *pBookView;
    QList<QWorksheetView*> mSheets;
    QMap<QString, QWorksheetView*> mNames;
    QMap<QWorksheetView*, bool> mRealnames;
    QWorksheetView* pCurrentWorksheet;
    QWorkbookToolBar *pToolbar;
    const PWorkbookParser pParser;

    Workbook* q_ptr;
    Q_DECLARE_PUBLIC(Workbook)
};


}

#endif // WORKBOOKPRIVATE_H
