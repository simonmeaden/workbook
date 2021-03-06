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
#ifndef WORKBOOKFONTTOOLBAR_H
#define WORKBOOKFONTTOOLBAR_H

#include <QFontComboBox>
#include <QComboBox>
#include <QIntValidator>
#include <QToolBar>

#include "workbook_global.h"
#include "qworkbookfonttoolbar_p.h"

namespace QWorkbook {

class QWorkbookView;
class QWorksheetView;
class FormatStatus;

class WORKBOOKSHARED_EXPORT QWorkbookFontToolBar : public QToolBar {
    Q_OBJECT
    Q_DECLARE_PRIVATE(QWorkbookFontToolBar)
public:
    QWorkbookFontToolBar(QWidget *parent);
    QWorkbookFontToolBar(QString title, QWidget *parent);
    virtual ~QWorkbookFontToolBar() {}

signals:
    void bold(bool);
    void italic(bool);
    void fontChanged(QFont);
    void fontSizeChanged(int);

public slots:
    void setFont(QFont);
    void setFont(bool, QFont, int);
    void setWorkbookView(QWorkbookView *);
    void setWorksheetView(QWorksheetView *);
    void selectionChanged(FormatStatus*);

protected slots:
    void fontHasChanged(QFont);
    void sizeHasChanged(QString);

protected:
    QWorkbookFontToolBar(QWorkbookFontToolBarPrivate &d, QWidget *parent) :
        QToolBar(parent),
        d_ptr(&d) {}
    QWorkbookFontToolBar(QWorkbookFontToolBarPrivate &d, QString title, QWidget *parent) :
        QToolBar(title, parent),
        d_ptr(&d) {}
    const QScopedPointer<QWorkbookFontToolBarPrivate> d_ptr;

private:

};


}

#endif // WORKBOOKFONTTOOLBAR_H
