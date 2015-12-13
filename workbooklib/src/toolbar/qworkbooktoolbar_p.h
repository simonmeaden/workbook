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
#ifndef QWORKBOOKTOOLBARPRIVATE_H
#define QWORKBOOKTOOLBARPRIVATE_H

#include <QMenu>
#include <QAction>
#include <QString>

#include "types.h"

#include "workbook_global.h"

namespace QWorkbook {

class QWorkbookToolBar;
class QWorkbookFontToolBar;
class QWorkbookFontEffectsToolBar;
class QWorkbookIndentToolBar;
class QWorkbookAlignToolBar;
class QWorkbookVerticalAlignToolBar;
class QWorkbookMergeToolbar;
class QWorkbookView;
class QWorksheetView;

class QWorkbookToolBarPrivate {
    Q_DECLARE_PUBLIC(QWorkbookToolBar)
public:
    QWorkbookToolBarPrivate(QWorkbookToolBar *parent);
    virtual ~QWorkbookToolBarPrivate() {}

    void selectionChanged(FormatStatus*);
    void setView(QObject *);

    void showFontBar(bool);
    void showFontEffectsBar(bool);
//    void showIndentBar(bool);
    void showAlignBar(bool);
    void showMergeBar(bool);


    void showContextMenu(const QPoint&);

protected:
    QWorkbookFontToolBar *pFontBar;
    QWorkbookFontEffectsToolBar *pFontEffectsBar;
//    QWorkbookIndentToolBar *pIndentBar;
    QWorkbookAlignToolBar *pAlignBar;
    QWorkbookVerticalAlignToolBar *pVAlignBar;
    QWorkbookMergeToolbar *pMergeBar;

    QMenu *pPopupMenu;
    QMenu *pToolbarMenu;

    QAction *pFontVisibleAction, *pFontEffectsVisibleAction, *pIndentVisibleAction, *pAlignVisibleAction;
    QAction *pMergeVisibleAction, *pVAlignVisibleAction;

    void init();

    QWorkbookToolBar *q_ptr;

};


}

#endif // QWORKBOOKTOOLBARPRIVATE_H
