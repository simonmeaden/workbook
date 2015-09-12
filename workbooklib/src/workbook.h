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
#ifndef WORKBOOK_H
#define WORKBOOK_H

#include <QObject>
#include <QString>
#include <QFileDialog>
#include <QScopedPointer>

#include "types.h"
#include "workbook_global.h"

class WorkbookPrivate;
class Worksheet;
class QWorksheetView;


class WORKBOOKSHARED_EXPORT Workbook : public QObject {
    Q_OBJECT
public:
    explicit Workbook(QObject *parent = 0);
    ~Workbook();

    int indexOf(Worksheet*sheet);
    int count();
    void setCurrentWorksheet(int index);
    void setCurrentWorksheet(QString name);
    Worksheet *addWorksheet();
    Worksheet *insertWorksheet(int index);
    int removeWorksheet(int index);
    int removeWorksheet(QString name);
    int removeWorksheet(Worksheet *sheet);
    int renameSheet(QString oldname, QString newname);

    static const QString SHEET; // base name for unnamed sheets
    static const QString SHEETNAME; // base name for unnamed sheets

signals:
    void namesChanged(int from);
    void sheetRemoved(int at);
    void sheetAdded(int at);

public slots:
    void saveWorkbook(QString filename);
    void saveWorkbook(QString filename, WorksheetType type);

protected slots:

protected:
    QScopedPointer<WorkbookPrivate> d_ptr;

    Worksheet* worksheet(int index);
    Worksheet* worksheet(QString name);
    Worksheet* currentWorksheet();

    friend class QWorkbookViewPrivate;

};

#endif // WORKBOOK_H
