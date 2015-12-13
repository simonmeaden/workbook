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
#include "workbook_p.h"

namespace QWorkbook {


class QWorksheetView;
class QWorkbookView;


class WORKBOOKSHARED_EXPORT Workbook : public QObject {
    Q_OBJECT
public:
    explicit Workbook(PWorkbookParser parser,
                      QWorkbookView *parent = 0);
    virtual ~Workbook() {}

    int indexOf(QWorksheetView*sheet);
    int size();
    void setCurrentWorksheetView(int index);
    void setCurrentWorksheetView(QString name);
    QWorksheetView *addWorksheet();
    QWorksheetView *insertWorksheet(int index, QWorksheetView *view);
    QWorksheetView *insertNewWorksheet(int index);
    int removeWorksheet(int index);
    int removeWorksheet(QString name);
    int removeWorksheet(QWorksheetView *sheet);
    int renameSheet(QString oldname, QString newname);
    void moveSheet(int, int);

    QStringList names();

    static const QString SHEET; // base name for unnamed sheets
    static const QString SHEETNAME; // base name for unnamed sheets

signals:
    void namesChanged(int from);
    void sheetRemoved(int at);
    void sheetAdded(int at);

public slots:
    void saveWorkbook(QString filename, WorksheetType type);

protected slots:

protected:
    QScopedPointer<WorkbookPrivate> d_ptr;

    QWorksheetView* worksheetView(int index);
    QWorksheetView* worksheetView(QString name);
    QWorksheetView* currentWorksheetView();

    friend class QWorkbookViewPrivate;

};


}

#endif // WORKBOOK_H
