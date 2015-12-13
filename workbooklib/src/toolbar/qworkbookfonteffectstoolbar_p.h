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
#ifndef QWORKBOOKFONTEFFECTSTOOLBARPRIVATE_H
#define QWORKBOOKFONTEFFECTSTOOLBARPRIVATE_H

#include <QPushButton>

#include "workbook_global.h"

namespace QWorkbook {

class QWorkbookFontEffectsToolBar;
class QWorkbookView;
class FormatStatus;

class QWorkbookFontEffectsToolBarPrivate {
    Q_DECLARE_PUBLIC(QWorkbookFontEffectsToolBar)
public:
    QWorkbookFontEffectsToolBarPrivate(QWorkbookFontEffectsToolBar *q);
    virtual ~QWorkbookFontEffectsToolBarPrivate() {}

    void setBold(bool);
    void setItalic(bool);
    void setUnderline(bool);
    void setView(QObject *);
    void selectionChanged(FormatStatus*);

protected:
    QPushButton *pBoldBtn, *pItalicBtn, *pUnderlineBtn;
    QWorkbookFontEffectsToolBar *q_ptr;
    QObject *pView;

    void init();
    void boldHasClicked();
    void italicHasClicked();
    void underlineHasClicked();

};


}

#endif // QWORKBOOKFONTEFFECTSTOOLBARPRIVATE_H
