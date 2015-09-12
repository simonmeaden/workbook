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
#ifndef QWORKBOOKFONTTOOLBARPRIVATE_H
#define QWORKBOOKFONTTOOLBARPRIVATE_H

#include <QPushButton>
#include <QFontComboBox>


class QWorkbookFontToolBar;
class QWorkbookView;
class FormatStatus;

class QWorkbookFontToolBarPrivate {
    Q_DECLARE_PUBLIC(QWorkbookFontToolBar)
public:
    QWorkbookFontToolBarPrivate(QWorkbookFontToolBar *q);
    virtual ~QWorkbookFontToolBarPrivate() {}

    void setFont(QFont);
    void setFont(bool, QFont, int);

    void fontHasChanged(QFont);
    void sizeHasChanged(QString);

    void setWorkbookView(QWorkbookView *);
    void selectionChanged(FormatStatus*);

protected:
    QFontComboBox *pFontCombo;
    QComboBox *pSizeCombo;
    QFontDatabase mFontDatabase;
    QWorkbookFontToolBar *q_ptr;

    void init();
    void setFontSizes(QFont font);


};

#endif // QWORKBOOKFONTTOOLBARPRIVATE_H
