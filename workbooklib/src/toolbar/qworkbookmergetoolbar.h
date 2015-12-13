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
#ifndef WORKBOOKMERGETOOLBAR_H
#define WORKBOOKMERGETOOLBAR_H

#include <QObject>
#include <QScopedPointer>
#include <QToolBar>

#include "qworkbookmergetoolbar_p.h"

#include "workbook_global.h"

namespace QWorkbook {

class QWorkbookView;
class QWorksheetView;
class FormatStatus;

class WORKBOOKSHARED_EXPORT QWorkbookMergeToolbar : public QToolBar {
    Q_OBJECT
    Q_DECLARE_PRIVATE(QWorkbookMergeToolbar)
public:
    QWorkbookMergeToolbar(QWidget *);
    QWorkbookMergeToolbar(QString, QWidget *);
    virtual ~QWorkbookMergeToolbar() {}

signals:
    void mergeChanged();

public slots:
    void setMerge(bool);
    void setWorkbookView(QWorkbookView *);
    void setWorksheetView(QWorksheetView *);
    void selectionChanged(FormatStatus*);

protected slots:
    void merge();

protected:
    QWorkbookMergeToolbar(QWorkbookMergeToolbarPrivate &d, QWidget *parent) :
        QToolBar(parent),
        d_ptr(&d) {}
   QWorkbookMergeToolbar(QWorkbookMergeToolbarPrivate &d, QString title, QWidget *parent) :
       QToolBar(title, parent),
       d_ptr(&d) {}
    const QScopedPointer<QWorkbookMergeToolbarPrivate> d_ptr;

private:

};


}

#endif // WORKBOOKMERGETOOLBAR_H
