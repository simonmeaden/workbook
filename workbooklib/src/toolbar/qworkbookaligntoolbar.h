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
#ifndef WORKBOOKALIGNTOOLBAR_H
#define WORKBOOKALIGNTOOLBAR_H

#include <QPushButton>
#include <QButtonGroup>
#include <QScopedPointer>
#include <QToolBar>

#include "workbook_global.h"
#include "qworkbookaligntoolbar_p.h"

namespace QWorkbook {

class QWorkbookView;
class QWorksheetView;
class FormatStatus;

class WORKBOOKSHARED_EXPORT QWorkbookAlignToolBar : public QToolBar {
    Q_OBJECT
    Q_DECLARE_PRIVATE(QWorkbookAlignToolBar)
public:
    QWorkbookAlignToolBar(QWidget*);
    QWorkbookAlignToolBar(QString, QWidget*);
    virtual ~QWorkbookAlignToolBar() {}

signals:
    void alignmentChanged(Qt::Alignment);

public slots:
    void setAlign(bool, Qt::Alignment);
    void setWorkbookView(QWorkbookView *);
    void setWorksheetView(QWorksheetView *);

protected slots:
    void alignHasClicked();
    void selectionChanged(FormatStatus*);

protected:
    QWorkbookAlignToolBar(QWorkbookAlignToolBarPrivate &d, QWidget *parent) :
        QToolBar(parent),
        d_ptr(&d) {}
    QWorkbookAlignToolBar(QWorkbookAlignToolBarPrivate &d, QString title, QWidget *parent) :
        QToolBar(title, parent),
        d_ptr(&d) {}
    const QScopedPointer<QWorkbookAlignToolBarPrivate> d_ptr;

private:

    friend class QWorkbookViewPrivate;

};

class WORKBOOKSHARED_EXPORT QWorkbookVerticalAlignToolBar : public QToolBar {
    Q_OBJECT
    Q_DECLARE_PRIVATE(QWorkbookVerticalAlignToolBar)
public:
    QWorkbookVerticalAlignToolBar(QWidget*);
    QWorkbookVerticalAlignToolBar(QString, QWidget*);
    virtual ~QWorkbookVerticalAlignToolBar() {}

signals:
    void alignmentChanged(Qt::Alignment);

public slots:
    void setAlign(bool, Qt::Alignment);
    void setWorkbookView(QWorkbookView *);
    void setWorksheetView(QWorksheetView *);

protected slots:
    void alignHasClicked();
    void selectionChanged(FormatStatus*);

protected:
    QWorkbookVerticalAlignToolBar(QWorkbookVerticalAlignToolBarPrivate &d, QWidget *parent) :
        QToolBar(parent),
        d_ptr(&d) {}
    QWorkbookVerticalAlignToolBar(QWorkbookVerticalAlignToolBarPrivate &d, QString title, QWidget *parent) :
        QToolBar(title, parent),
        d_ptr(&d) {}
    const QScopedPointer<QWorkbookVerticalAlignToolBarPrivate> d_ptr;

private:

    friend class QWorkbookViewPrivate;

};



}

#endif // WORKBOOKALIGNTOOLBAR_H
