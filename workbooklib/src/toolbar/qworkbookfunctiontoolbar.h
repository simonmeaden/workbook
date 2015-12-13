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
#ifndef WORKBOOKFUNCTIONTOOLBAR_H
#define WORKBOOKFUNCTIONTOOLBAR_H

#include <QPlainTextEdit>
#include <QPushButton>
#include <QToolButton>
#include <QLineEdit>
#include <QToolBar>

#include "qworkbookfunctiontoolbar_p.h"

#include "workbook_global.h"

namespace QWorkbook {

class QWorkbookView;
class FormatStatus;

class WORKBOOKSHARED_EXPORT QWorkbookFunctionToolBar : public QToolBar {
    Q_OBJECT
    Q_DECLARE_PRIVATE(QWorkbookFunctionToolBar)
public:
    QWorkbookFunctionToolBar(QWidget *parent);
    QWorkbookFunctionToolBar(QString title, QWidget *parent);
    virtual ~QWorkbookFunctionToolBar() {}

signals:

public slots:
    void setRange(QString value);

protected slots:
    void drop();
    void manageNames();
    void functionWizard();
    void sum();
    void function();

protected:
    QWorkbookFunctionToolBar(QWorkbookFunctionToolBarPrivate &d, QWidget *parent) :
        QToolBar(parent),
        d_ptr(&d) {}
    QWorkbookFunctionToolBar(QWorkbookFunctionToolBarPrivate &d, QString title, QWidget *parent) :
        QToolBar(title, parent),
        d_ptr(&d) {}
    QScopedPointer<QWorkbookFunctionToolBarPrivate> d_ptr;

private:

};


}

#endif // WORKBOOKFUNCTIONTOOLBAR_H
