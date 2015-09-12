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

class Workbook;
class Worksheet;
class QWorkbookToolBar;

class WorkbookPrivate {
public:
    WorkbookPrivate(Workbook *parent);
    ~WorkbookPrivate();

    Worksheet* worksheet(int index);
    Worksheet* worksheet(QString name);
    Worksheet* currentWorksheet();
    void setCurrentWorksheet(int index);
    void setCurrentWorksheet(QString name);
    Worksheet *addWorksheet();
    Worksheet* insertWorksheet(int index);
    int indexOf(Worksheet*);
    inline int count() { return mSheets.size(); }

    int removeWorksheet(int index);
    int removeWorksheet(QString name);
    int removeWorksheet(Worksheet *sheet);
    int renameSheet(QString oldname, QString newname);

    void saveWorkbook(QString filename);
    void saveWorkbook(QString filename, WorksheetType type);
    void saveOds(QString filename);
    void saveXls(QString filename);
    void saveXlsx(QString filename);
    void loadWorkbook(QString filename);

    void setToolbar(QWorkbookToolBar *pToolbar);

protected:
    void renameSheets(int index);
    bool areNumbers(QString str);
    bool isRealName(QString str);

    QList<Worksheet*> mSheets;
    QMap<QString, Worksheet*> mNames;
    QMap<Worksheet*, bool> mRealnames;
    Worksheet* pCurrentWorksheet;
    QWorkbookToolBar *pToolbar;
    PluginStore *pPluginStore;

    Workbook* q_ptr;
    Q_DECLARE_PUBLIC(Workbook)
};

#endif // WORKBOOKPRIVATE_H
