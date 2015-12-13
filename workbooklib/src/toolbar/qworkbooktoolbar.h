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
#ifndef WORKSHEETTOOLBAR_H
#define WORKSHEETTOOLBAR_H

#include <QWidget>
#include <QToolBar>
#include <QButtonGroup>
#include <QAction>
#include <QShortcut>
#include <QIcon>
#include <QMenu>

#include "workbook_global.h"
#include "range.h"
#include "qworkbookview.h"
#include "qworkbookfonttoolbar.h"
#include "qworkbookfonteffectstoolbar.h"
#include "qworkbookaligntoolbar.h"
#include "qworkbookmergetoolbar.h"
#include "qworkbookindenttoolbar.h"
#include "qworkbooktoolbar_p.h"


namespace QWorkbook {


class WORKBOOKSHARED_EXPORT QWorkbookToolBar : public QToolBar {
    Q_OBJECT
public:
    QWorkbookToolBar(QWidget *parent);
    QWorkbookToolBar(QString title, QWidget *parent);
    ~QWorkbookToolBar() {}

signals:

public slots:
    void selectionChanged(FormatStatus*);
    void setWorkbookView(QWorkbookView *);
    void setWorksheetView(QWorksheetView *);

    void showFontBar(bool);
    void showFontEffectsBar(bool);
//    void showIndentBar(bool);
    void showAlignBar(bool);
    void showMergeBar(bool);

protected slots:
    void showContextMenu(const QPoint&);

protected:
    const QScopedPointer<QWorkbookToolBarPrivate> d_ptr;

private:
    Q_DECLARE_PRIVATE(QWorkbookToolBar)

};


}

#endif // WORKSHEETTOOLBAR_H
