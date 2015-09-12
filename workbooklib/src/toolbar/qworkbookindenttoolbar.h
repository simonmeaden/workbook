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
#ifndef WORKBOOKINDENTTOOLBAR_H
#define WORKBOOKINDENTTOOLBAR_H

#include <QPushButton>
#include <QScopedPointer>
#include <QToolBar>

#include "workbook_global.h"
#include "qworkbookindenttoolbar_p.h"

class QWorkbookView;
class FormatStatus;

class WORKBOOKSHARED_EXPORT QWorkbookIndentToolBar : public QToolBar {
    Q_OBJECT
    Q_DECLARE_PRIVATE(QWorkbookIndentToolBar)
public:
    QWorkbookIndentToolBar(QWidget *parent);
    QWorkbookIndentToolBar(QString title, QWidget *parent);
    virtual ~QWorkbookIndentToolBar() {}

signals:
    void indentCells();
    void undentCells();

public slots:

protected slots:
    void indent();
    void undent();

protected:
    QWorkbookIndentToolBar(QWorkbookIndentToolBarPrivate &d, QWidget *parent) :
        QToolBar(parent),
        d_ptr(&d) {}
    QWorkbookIndentToolBar(QWorkbookIndentToolBarPrivate &d, QString title, QWidget *parent) :
        QToolBar(title, parent),
        d_ptr(&d) {}
    QScopedPointer<QWorkbookIndentToolBarPrivate> d_ptr;

    void init();

private:

};
#endif // WORKBOOKINDENTTOOLBAR_H
